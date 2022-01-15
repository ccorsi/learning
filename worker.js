// ==================================================================================================
//
// Copyright 2022 Claudio Corsi
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

var backgroundPort = browser.runtime.connect({name: backgroundTrackerPortName});

backgroundPort.onMessage.addListener(updateList);

// ===================================================================================================
// updateList(message)
//      message: message sent from the background script
//
//  This method will process the activity information that was sent from the background script about
//  a given web page activity.  This function will update the list that contain this information that
//  will be displayed to the user.
//
//
//  <ul id="times">
//      <li>
//          <span class="caret">host name and total activity time</span>
//          <ul class="nested">
//              <li>activity information with date</li>
//              <li>activity information with date</li>
//              ...
//          </ul>
//      </li>
//      <li>
//          <span class="caret">host name and total activity time</span>
//          <ul class="nested">
//              <li>activity information with date</li>
//              <li>activity information with date</li>
//              ...
//          </ul>
//      </li>
//  </ul>
//
// ===================================================================================================

function updateList(message) {
    // We will need to update the current window with this information and then continue
    send_notification('Web Page Tracker Time Control Manager', 'Received the following message: ' + message);
    var name = message.host;
    var date = message.date;
    var activity = message.activity;

    var elem = document.getElementById(name);

    try {
    if (elem == null) {
        send_notification('Web Page Tracker Time Control Manager', '** host element: ' + name + ' was not found');
        // get a reference to the unordered list
        var times = document.getElementById('times');
        // create a new li element and add it to the main document.
        var li = document.createElement('li');
        times.appendChild(li);
        // create a span element
        var span = document.createElement('span');
        // an a class attribute defined as caret
        span.setAttribute('class', 'caret');
        span.setAttribute('id', name);
        span.setAttribute('total', activity);
        // set the innerText to the current name and total time
        span.innerText = name + " with total time " + format_time(activity);
        // add listener for click events
        span.addEventListener('click', function() {
            this.parentElement.querySelector(".nested").classList.toggle("active");
            this.classList.toggle("caret-down");
        });
        li.appendChild(span);
        // create a ul element
        var ul = document.createElement('ul');
        // set the class attribute to nested
        ul.setAttribute('class', 'nested');
        li.appendChild(ul);
        // create another li element to store the current activity
        li = document.createElement('li');
        li.innerText = date + " time: " + format_time(activity);
        ul.appendChild(li);
    } else {
        send_notification('Web Page Tracker Time Control Manager', '** host element: ' + name + ' was found');
        console.debug('Iterating over the element ' + elem.parentElement.tagName + ' that has ' + elem.parentElement.children.length + ' children.');
        let children  = elem.parentElement.children;
        // find the span element child and update the activity time
        for (let idx = 0 ; idx < children.length ; idx++ ) {
            let element = children[idx];
            console.debug('Processing element with tag name: ' + element.tagName);
            if (element.tagName == 'SPAN') {
                console.debug('Found a span element');
                var span = element;
                // get the total string and convert into a number
                var total = parseInt(span.getAttribute('total'));
                // Add the current activity to the total amount for the given host.
                total += activity;
                // update the total attribute and total value of the innerText
                span.setAttribute('total', total);
                // update the innerText of the span to include the total update
                span.innerText = name + " with total time " + format_time(total);
            } else if (element.tagName == 'UL') {
                console.debug('Found a ul element');
                var ul = element;
                // create another li element to store the current activity
                li = document.createElement('li');
                li.innerText = date + " time: " + format_time(activity);
                ul.appendChild(li);
            } else {
                console.debug('Skipping element with tag name: ' + element.tagName);
            }
        }
        console.debug('Completed processing children for element ' + elem.tagName);
    }
    } catch(error) {
        send_notification('web Page Tracker Time Control Manager', 'An exception was raised when updating list: ' + error);
    }
}

/****************************************************************************************************************************************************
 
// Open an indexed database

const timetrackerDBName = 'TimeTrackerDatabase';

// state the different steps that we are going to be performing when trying to open the datastore.
//
// start datastore open action
// completed datastore open action
// 
// We now need to let the user know that the action of opening the datastore was successful or not
//
// success
// failure
// notavailable

let openedDataStore =  false;
let timetrackerDB = undefined;
let queue = []; // this is a queue that will be used to store received web page tracking data that we were unable to store since the database has not been opened already.

if (window.indexedDB) {
    // Note that these are all async calls that are performed on the given datastore.
    var request = window.indexedDB.open(timetrackerDBName, 1);

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

    request.onupgradeneeded = function() {
        // log that we are upgrading and/or updating the database since the version does not comply.
        console.debug('Received an upgrade needed event for the ' + timetrackerDBName + ' database.');
        send_notification('Web Page Tracker DataStore', 'Upgrading the current ' + timetrackerDBName + ' database.');
    }

} else {
    console.error("This browser does not support indexedDB");
    // We set that the datastore was opened
    openedDataStore = true;
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
        try {
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
        } catch(error) {
            console.error('Tracker BackGround: Received an exception while processing datastore calls: ' + error);
        }
    } else {
        queue.push(message);
    }
}

 ****************************************************************************************************************************************************/
