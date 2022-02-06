// ==================================================================================================
//
// Copyright 2022- Claudio Corsi
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// ==================================================================================================

// ==============================================================================================================
//
// This background time tracker script will receive updates from the different web page activites and will
// store this information within a local datastore and send a notification about the current update.
//
// ==============================================================================================================

// Create a new window that will contain the web page time tracker control window

// This is the window id of the web page time tracker control window.  This will be used to send the window messages
// that are being received from the timetracker content script.  This script will store the contents that are being
// generated to a local datastore and the control window will be responsible to show the current set of information
// that the user will want to see displayed.  It can also be used to perform other tasks that the user chooses to 
// perform.

// We will create a connection based messaging

var backgroundPort = 0;

browser.runtime.onConnect.addListener(function(port) {
    console.debug('The connection: ' + port + ' was created.');
    backgroundPort = port;
    // Listen to the given port for messages that will be stored
    backgroundPort.addListener(notify);
});

function oncreate(windowInfo) {
    console.debug('The Web Page Tinme Tracker Control Window was successfully created: ' + windowInfo.id);
    console.debug('Window Info: ' + windowInfo);
}

function onerror(error) {
    console.error('The Web Page Time Tracker Control Windows generated an error: ' + error);
}

try {
    var controlWindow = browser.extension.getURL("timetracker.html");

    var creating = browser.windows.create({
        url: controlWindow,
        type: "detached_panel"
        // Should I consider associating a width and height values for the opening of the new window?
    });

    creating.then(oncreate, onerror);    
} catch(error) {
    console.error('An error was generated when creating the web page time tracker console page: ' + error);
}

/****************************************************************************************************************************************************/

// Open an indexed database

const timetrackerDBName = 'TimeTrackerDatabase';
let openedDataStore =  false;
let timetrackerDB;

if (window.indexedDB) {
    // Note that these are all async calls that are performed on the given datastore.
    var request = window.indexedDB.open(timetrackerDBName, 2);

    request.onupgradeneeded = function() {
        // Get a reference to the opened database
        const db = request.result;
        console.debug('Creating the ObjectStore: ' + timetrackerDBName);
        const store = db.createObjectStore(timetrackerDBName, {keypath : 'date'});
        console.debug("The ObjectStore: " + timetrackerDBName + " has been created");
    }

    request.onerror = function(event) {
        // log that there was an error opening the datastore and set the openedDataStore to false
        console.error('Unable to open the indexedDB TimeTraceDatabase with error code: ' + request.errorCode);
        openedDataStore = false;
        browser.notifications.create("Web Page Tracker DataStore", "The TrackerDataStore was not successfully opened");
        send_notification("Web Page Tracker DataStore", 'The TrackerDataStore was not successfully opened: ' + event.target.error);
    }

    request.onsuccess = function(event) {
        // log that we were able to successfully open the datastore and set the openedDataStore to true
        console.log('Successfully opened the indexedDB TimeTraceDatabase');
        openedDataStore = true;
        timetrackerDB = request.result;
        send_notification("Web Page Tracker DataStore", "The TrackerDataStore was successfully opened");
    }

} else {
    console.error("This browser does not support indexedDB");
}

// Register the listener that will receive the different messages that are sent by the content script.
browser.runtime.onMessage.addListener(notify)

// ==============================================================================================================
// notify(message)
//     message: json object that contain information from the message sent by the timetracker content script.
//
// This method will receive messages sent by the different web pages that contain the times that the user was
// actively viewing a particuler web site.  The information will be store within a datastore and a notification
// will be generated that includes information about the current start of the web page activety.
//
// ==============================================================================================================
function notify(message) {

    // forward the message to the control panel to update the list
    backgroundPort.postMessage(message);

    const content = "Host: " + message.host + " was viewed for " + message.activity + " on " + message.date;

    // Generate a notification about which web page generated some activity information.
    send_notification("Web Page Activity", content);

    // Log the notification message
    console.debug("Tracker BackGround: Processing message for host: " + message.host + " at " + message.date +
       " with accumulated time elapsed: " + message.activity);

    if (openedDataStore) {
        try {
            // Only store the times locally if the browser supports the indexedDB datastore mechanism.
            const txn = timetrackerDB.transaction([timetrackerDBName], 'readwrite', {"durability": "strict"});

            txn.oncomplete = function(event) {
                // The transaction completed successfully
                send_notification("Web Page Tracker DataStore", "Successfully completed a indexedDB transaction for message: { " + message.host +
                    ", " + message.activity + ", " + message.date + " }");
            }

            txn.onerror = function(event) {
                // An error was encountered when processing this transaction
                send_notification("Web Page Tracker DataStore", "indexedDB transaction generated an error with code: " + event.errorCode + " for messsage: { " +
                    message.host + ", " + message.activity + ", " + message.date + " }");
            }

            const store = txn.objectStore(timetrackerDBName);

            // Store the passed entry into the datastore
            store.put({host: message.host, activity: message.activity, date: message.date});

            txn.oncomplete =  function() {
                console.debug('Successfully stored the entry: { ' + message.host + ", " + message.activity + ", " + message.date + " }");
            }

        } catch(error) {
            console.error('Tracker BackGround: Received an exception while processing datastore calls: ' + error);
        }
    } else {
        send_notification("Web Page Tracker DataStore", "ObjectStore was not initialized for messsage: { " +
            message.host + ", " + message.activity + ", " + message.date + " }");
    }
}
 
/****************************************************************************************************************************************************/
