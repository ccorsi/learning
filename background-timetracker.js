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

// Open an indexed database

const timetrackerDBName = 'TimeTrackerDatabase';
let openedDataStore =  false;
let timetrackerDB;

if (window.indexedDB) {
    // Note that these are all async calls that are performed on the given datastore.
    var request = window.indexedDB.open(timetrackerDBName, 1);

    request.onerror = function(event) {
        // log that there was an error opening the datastore and set the openedDataStore to false
        console.error('Unable to open the indexedDB TimeTraceDatabase with error code: ' + request.errorCode);
        openedDataStore = false;
        send_notification()
        browser.notifications.create("Web Page Tracker DataStore", "The TrackerDataStore was not successfully opened");
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

    const content = "Host: " + message.host + " was viewed for " + message.activity + " on " + message.date;

    // Generate a notification about which web page generated some activity information.
    send_notification("Web Page Activity", content);

    // Log the notification message
    console.debug("Tracker BackGround: Processing message for host: " + message.host + " at " + message.date +
       " with accumulated time elapsed: " + message.activity);

    if (openedDataStore) {
        // Only store the times locally if the browser supports the indexedDB datastore mechanism.
        var txn = timetrackerDB.transaction([timetrackerDBName], 'readwrite', {"durability": "strict"});

        txn.oncomplete = function(event) {
            // The transaction completed successfully
            send_notification("Web Page Tracker DataStore", "Successfully completed a indexedDB transaction");
        }

        txn.onerror = function(event) {
            // An error was encountered when processing this transaction
            send_notification("Web Page Tracker DataStore", "indexedDB transaction generated an error with code: " + event.errorCode);
        }

        var objectStore = txn.objectStore(timetrackerDBName);

    }
}
