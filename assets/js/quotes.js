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
