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

// ====================================================================================================
// 
// This is a simple plugin that will track the amount of time that someone is on a given web site.  It
// will then store the total amount within a database everytime that there is an update, (ok this is not
// the most efficient way of doing this since it isn't clear how to handle the case that the user is
// leaving a given web site and/or exiting the browser but it will hopefully be optimized in the future).
//
// The following contains points that need to be addressed about how to implement this simple plugin
// to we used within FireFox and/or other browsers like Chrome, Edge, Opera and others.  This is more
// as a proof of concept that I am able to create and implement these type of plugins.
//
// Q: Will the generated indexedDB contain all of the times for all the web sites or will it contain
//    it only for a given web site?
//
// Q: How can we access the indexedDB values when the users what to generate a report of the data?
//    For instance, how to generate a display of the total times spent at different web sites?
//
// Q: Show I consider using some of the analytics tools that are available like Google, Facebook and 
//    probably other services to store the information for a given user information.  It can then be
//    used to produce reports for whoever is interested in 'looking' at ones web browsing tendencies.
//
// ====================================================================================================

// The following class will accumulate the total amount of time that the user is focus on the 
// current window.  
// 
// It currently does not know how to handle the event that the window is in focus and the user
// is not doing anything.  It is possible that the user is reading an article and will only 
// generate events when he needs to scroll. Maybe the tracker should try to learn when the
// user is actively using the window or not.

console.debug('Called tracker plugin for host: ' + window.location.host);

class Tracker {
    
    constructor() {
        this.total = 0;
        // This is useful in the case that we've opened a new web site within the same window.
        // The focus event is not generated since you are already "focused" within that window. 
        this.start = new Date();
        console.debug('Tracker: Called the constructor');
    }

    start_event(event) {
        this.start = new Date();
        console.debug('Tracker: Called focus event with time: ' + this.start);
    }

    end_event(event) {
        try {
            let end = new Date();
            console.debug('Tracker: Called blur event with time: ' + end);
            // console.debug('Tracker: this.start: ' + this.start);
            let current = end.getTime() - this.start.getTime();
            // console.debug('Tracker: this.total: ' + this.total);
            this.total += current;
            console.debug('Tracker: Called blur event with time: ' + end + " with currently elapsed time: " + current + " and total time: " + this.total + " for host: " + window.location.host);
            // Send a message that will be processed by the background process that will then raise a notification.
            browser.runtime.sendMessage({"host": window.location.host, "date": this.start, "activity": current});
        } catch(error) {
            console.debug('Tracker: An exception was raised: ' + error);
        }
    }

    close_event(event) {
        console.debug('Tracker: Called close event for host: ' + window.location.host + " with total time: " + this.total);
    }
}

console.debug('Tracker: creating the Tracker object');
const tracker = new Tracker();
console.debug('Tracker: created the Tracker object');

// ================================================================================
// start_event(event)
//     event: a windows event, specically the focus event
//
//  This method will set the start value to the current Date/Time that will be used
//  to determine the amount of time that a user was focused on a given web page.
//
//
// ================================================================================
function start_event(event) {
    // This action will override the initial start value only in the case mentioned above
    // tracker.start_event(event);
    log_function_call('start_event', tracker, tracker.start_event, event);
}

// ================================================================================
// end_event(event)
//     event: a windows event, specically the blur event
//
//  This method will is used to gather the current Date/Time and then differentiate
//  from the prior start value which will be the current total time that a user was
//  actively looking at a given web page.  The current value will then be aggregated
//  with the current running total for the given web site.  This will then be stored
//  within a datastore.  This datastore can be local or remote depending on how the
//  method will be implemented.
//
// ================================================================================
function end_event(event) {
    // tracker.end_event(event);
    log_function_call('end_event', tracker, tracker.end_event, event);
}

// ================================================================================
// end_event(event)
//     event: a windows event, specically the beforeunload event
//
// This method will be called whenever the window is being unloaded.  It is currently
// a noop action but it can become more actionable in future versions of this plugin.
//
// ================================================================================
function beforeunload_event(event) {
    // console.log('Called beforeunloaded event: ' + event);
    // tracker.close_event(event);
    log_function_call('close_event', tracker, tracker.close_event, event);
}

try {
    // Add tracker events for the onfocus, onblur and onclose events.
    console.debug('Tracker: Added the event listerners');
    window.addEventListener("focus", start_event);
    console.debug('Tracker: Added the focus event listener');
    window.addEventListener("blur", end_event);
    console.debug('Tracker: Added the blur event listener');
    window.addEventListener("beforeunload", beforeunload_event);
    console.debug('Tracker: Added the beforeunload event listener');
} catch(error) {
    console.error('An exception was raised when adding event listerns with exception: ' + error);
}
