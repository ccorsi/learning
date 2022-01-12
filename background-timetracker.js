// ==============================================================================================================
//
// This background time tracker script will receive updates from the different web page activites and will
// store this information within a local datastore and send a notification about the current update.
//
// ==============================================================================================================

// Open an indexed database

let openedDataStore =  false;
let timetrackerDB;

if (window.indexedDB) {
    // Note that these are all async calls that are performed on the given datastore.
    var request = window.indexedDB.open('TimeTrackerDatabase', 1);

    request.onerror = function(event) {
        // log that there was an error opening the datastore and set the openedDataStore to false
        console.error('Unable to open the indexedDB TimeTraceDatabase with error code: ' + request.errorCode);
        openedDataStore = false;
        browser.notifications.create({
            "type":"basic",
            "title": "Web Page Tracker DataStore",
            "message": "The TrackerDataStore was not successfully opened"
        });
    }

    request.onsuccess = function(event) {
        // log that we were able to successfully open the datastore and set the openedDataStore to true
        console.log('Successfully opened the indexedDB TimeTraceDatabase');
        openedDataStore = true;
        timetrackerDB = request.result;
        browser.notifications.create({
            "type":"basic",
            "title": "Web Page Tracker DataStore",
            "message": "The TrackerDataStore was successfully opened"
        });
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
    browser.notifications.create({
        "type": "basic",
        "title": "Web Page Activity",
        "message": content
    });

    // Log the notification message
    console.debug("Tracker BackGround: Processing message for host: " + message.host + " at " + message.date +
       " with accumulated time elapsed: " + message.activity);

    if (openedDataStore) {
        // Only store the times locally if the browser supports the indexedDB datastore mechanism.
    }
}
