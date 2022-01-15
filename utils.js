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

// ==================================================================================================
//
// utils.js
//
// This file contains general functions and classes that will be used by the different scripts of
// this plugin.
//
// ==================================================================================================

// The following constant definitions are the port names used for the connection based messaging interaction
// between the content, background and control window.

const backgroundTrackerPortName = 'background-tracker-port';

// ================================================================================
// send_notification(title, message)
//      title: title passed to the notification create method call
//      message: message passed to the notification create method call
//
// This function will create a notification message that will then be displayed to
// the user of this plugin.
//
// ================================================================================

function send_notification(title, message) {
    console.debug('Tracker: creating a notification with title: ' + title + " containing message: " + message);
    browser.notifications.create({
        "type":"basic",
        "title": title,
        "message": message
    });
    console.debug('Tracker: created notification');
}

// ================================================================================
// log_function_call(name, func, event)
//      name: the name of the function being passed
//      func: the function that will be called
//      event: the event that will be passed to the passed function
//
// This function will log function calls that where generated by the event listener.
// It will log the call before it is called and then log the call after it was
// called.
//
// ================================================================================

function log_function_call(name, obj, func, event) {
    try {
        console.debug('Tracker: calling the ' + name + ' function.');
        func.call(obj, event)
    } catch(error) {
        console.error('Tracker: an exception was raised when calling the functin: ' + name + ' with error code: ' + error);
    } finally {
        console.debug('Tracker: called the ' + name + ' function.');
    }
}

function format_time(time) {
    console.debug('Formating time: ' + time);
    const millis = time % 1000;
    // console.debug('Milliseconds: ' + millis);
    time /= 1000; time = Math.floor(time);
    // console.debug('Updated time: ' + time);
    let formatted = '' + millis + 'ms';

    if (time != 0) {
        const seconds = time % 60;
        // console.debug('Seconds: ' + seconds);
        time /= 60; time = Math.floor(time);
        // console.debug('Updated time: ' + time);

        if (seconds > 0) formatted = '' + seconds + 's ' + formatted;
    }

    if (time != 0) {
        const minutes = time % 60;
        // console.debug('Minutes: ' + minutes);
        time /= 60; time = Math.floor(time);
        // console.debug('Updated time: ' + time);

        if (minutes > 0) formatted = '' + minutes + 'm ' + formatted;
    }

    if (time != 0) {
        const hours = time % 24;
        // console.debug('Hours: ' + hours);
        time /= 24; time = Math.floor(time);
        // console.debug('Updated time: ' + time);

        if (hours > 0) formatted = '' + hours + 'h ' + formatted;
    }

    if (time != 0) {
        const days = time;
        // console.debug('Days: ' + days);

        formatted = '' + days + 'd ' + formatted;
    }

    formatted = '"' + formatted + '"';

    console.debug('Returning formatted time: ' + formatted);

    return formatted;
}