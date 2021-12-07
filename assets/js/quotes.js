---
layout: null
---

/*
  License:

  Copyright 2021 Claudio Corsi

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
  documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
  persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
  Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
  OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  */

/*
  
  This file will contain classes and functions that will be used to generate a
  random quote from a given file.  The file will be formatted as a JSON array
  where each entry in the array will contain a author and quote property.  The
  author property will be a simple string that will contain the name of the 
  author of the associated quote.  While the quote property will be a JSON array
  where each entry is a single line of the quote.  The loading mechanism will 
  then be able to use this information to determine if it chooses to display
  each quote line on its own line or within a single line.

 */

/*
const object1 = {
  a: 'somestring',
  b: 42,
  c: false
};

const object = [
  { "author": "me",
    "quotes": [ "Line one", "Line two" ],
  },
  { "author": "you",
   "quotes": [ "Line one", "Line two", "Line three" ],
  },
];

// This function will return an integer values between 0 and max-1.
function getRandomInt(max) {
  return Math.floor(Math.random() * max);
};

console.log(Object.keys(object1));
// expected output: Array ["a", "b", "c"]
console.log(object[getRandomInt(object.length)]);

function printQuote(entry) {
  console.log(entry)
};

function printEntry(entry) {
  console.log(entry.author)
  entry.quotes.forEach(e => printQuote(e))
};

if (typeof object != "undefined") {
  console.log("Object is non-null");
  object.forEach(entry => printEntry(entry))
}

if (typeof foo == "undefined") {
  console.log("Object foo is not defined")
}
*/
/*
  This class is used to select a single quote from an given
  json file.  It will expect the uri to the json file that
  contains the quotes.  It will then load and randomly 
  select one of the quotes from the file.  The quote will
  be returned to the caller in which they will decide
  how to format the given quote.

  Quotes file format:

  The quotes file will be a simple JSON array that will contain
  two fields for array element.  They are the "author" and "quotes"
  fields.  The author field a simple string while the quotes field
  is an array where each entry will be displayed on its own line.
  This will allow the caller to decide if the quote should be 
  displayed on a single or multiple lines.

  For example:

  [
    {
      "author": "Joe Blow",
      "quote": [
            "Joe Blow line quote one",
	    "Joe Blow line quote two",
         ],
    },
    {
      "author": "Joe Inhale",
      "quote": [
            "Joe Inhale line quote one",
	    "Joe Inhale line quote two",
         ],
    },
  ]

 */

/*
class Quotes {
  callbacks = [];

  constructor(url) {
    // Open a HttpXRequest to retrieve the quotes and apply them to 
    // a field within the Quotes class
    var xhr = new XMLHttpRequest();
    xhr.open("GET", url);
//     xhr.setRequestHeader('Content-Type', 'application/json');
//     xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
    xhr.responseType = 'json';
    xhr.send();
    xhr.onload = function() {
      // This is called whenever the call was successful.
    };
    xhr.onerror = function() {
    };
    xhr.onreadystatechange = function () {
      if(xhr.readyState === XMLHttpRequest.DONE) {
        var status = xhr.status;
        if (status >= 200 && status < 400) {
          this.get_quote = function() {
	  };
	  // Assign the resulting call to the function call
	  this.get_quote.quotes = xhr.responseText;
        } else {
          this.get_quote = function() {
	    return {
	      "author" : "",
	      "quote" : [],
	    };
	  };
        }
      }
    };
  }
  // This method will load the quotes file and randomly select
  // a given quote.  It will then pass the selected quote to
  // the passed callback to process.
  get quote(callback) {
    // Load the file from the server
  }
}

const quotes = new Quotes("/assert/data/quotes.json");

quotes.quote(callback); // This will return a quote from the quotes file.

function callback(quote) {
}
*/


/*
// This method will return a random number from 0 to max - 1.
function getRandomInt(max) {
  return Math.floor(Math.random() * max);
};

// This method will display a random quote retrieved from the
// given url for the passed element id.
function getQuote(url, elm) {
  let request = new XMLHttpRequest();
  request.open('GET', url);
  request.responseType = 'json';
  request.send();
  request.onload = function() {
    // This method will randomly select a quote and then display it
    const quotes = request.response;
    const quote = quotes[getRandomInt(quotes.length)];
    var div = document.createElement('div');
    div.setAttribute('align','left');
    div.append(document.createElement('br'));
    quote.quote.forEach(e => {
	div.append(e);
	div.append(document.createElement('br'));
      });
    elm.append(div);
    var div = document.createElement('div');
    div.setAttribute('align','right');
    div.append(document.createElement('br'));
    div.append('"');
    div.append(quote.author);
    div.append('"');
    div.append(document.createElement('br'));
    elm.append(div);
  };
};
*/

// This method will return a random number from 0 to max - 1.
function getRandomInt(max) {
   return Math.floor(Math.random() * max);
};

// This method will display a random quote retrieved from the
// given url for the passed element id.
function getQuote(url, elm) {
  let request = new XMLHttpRequest();
  request.open('GET', url);
  request.responseType = 'json';
  request.send();
  request.onload = function() {
     // This method will randomly select a quote and then display it
     const quotes = request.response;
     const quote = quotes[getRandomInt(quotes.length)];
     var div = document.createElement('div');
     div.setAttribute('style','text-align: left;');
     div.append(document.createElement('br'));
     quote.quote.forEach(e => {
        div.append(e);
        div.append(document.createElement('br'));
     });
     elm.append(div);
     var div = document.createElement('div');
     div.setAttribute('style','text-align: right;');
     div.append(document.createElement('br'));
     div.append('"');
     div.append(quote.author);
     div.append('"');
     div.append(document.createElement('br'));
     elm.append(div);
   };
};

/*
Local Variables:
backup-inhibited: t
End:
 */
