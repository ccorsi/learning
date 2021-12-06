---
layout: resume
title: C/C++ Programming Language
subtile: What I Learned
---

{% comment %}
# TODO: Describe the different c/c++ tools that I have used and learned through work and exploration
of the c/c++ programming language.

# Introduction

This page will contain a more detailed version of the knowledge and experience that I have gained using the
C/C++ programming language.  It will expand on the information that is contained within my official resume
available [here](https://raw.githubusercontent.com/ccorsi/learning/docs/assets/pdf/ClaudioCorsiCV.pdf).  I
will discuss when, where and what I have learned using the C and C++ language.  This section will also 
include knowledge that I have gained that was outside of a work environment pertaining to the C/C++ 
programming language.

# Work Experience

I have exclusively used the C programming language in my first two jobs at Ranmar and Bell Sygma.  While I have also
used C at other jobs but those have been in conjunction with C++ which will be discussed later on in this section.  
While that use of C at Ranmar was within the context of a mature product and the use of C at Bell Sygma was used 
in the context of a brand new product.  

# Non-Work Experience



{% endcomment %}

# Introduction

This page will contain a more detailed version of the knowledge and experience that I have gained using the
C/C++ programming language.  It will expand on the information that is contained within my official resume
available [here](https://raw.githubusercontent.com/ccorsi/learning/docs/assets/pdf/ClaudioCorsiCV.pdf).  I
will discuss when, where and what I have learned using the C and C++ language.

# C

## Work Experience

I have exclusively used the C programming language mainly within my first two jobs at Ranmar and Bell Sygma.
While I have also used C at other jobs but those have been in conjunction with C++ which will be expanded
within the next section.  In this section, I expand on how I've used the C programming language within the
context of the two jobs I mentioned above.

The use of the C programming language within Ranmar entailed the development of a financial software that
was used by one or more customers.  The software used a client-server architecture where the client was
initially a dos program that would access a server that was running on IBM AIX operating system.  When I
started at the job, the product was fairly mature and I was initially asked to fix bugs.  These included
simple fixes to the software that allowed me to get aquainted with the software.  I was then asked to
add a major addition to the product that offered a new feature of the product.  This required that I had
to understand how menu was generated using function pointers.  This project was developed such that it
would use the feature of being able to communicate with the server.  After completing this work on the
product, my manager asked me to work on upgrading the product from using a dos terminal client to using a
windows client.  This work required that I create a protocol that was used by the windows client such that
the server can dynamically generate a given window on the windows client that would be able to process the
same set of functionality that the dos client terminal was processing.  Since, the browser was still not
what it is now and we were using Windows 3.1.  I was not able to take advantage of all the advantage that
a web browser was able to offer.  In that respect, the creation of a simple protocol that provided the
necessary functionality to perform similar tasks as the dos client terminal was a challenge in itself.

While at Bell Sygma I was developing a product from scrarch that required that I design two different
application that would perform different tasks.  There is a program that needed to receive data from a
DMS switch which is major telephone switch.  The data will contain information about the different
incoming telephone calls.  This information was defined by a protocol that was designed by the DMS
switch company.  I needed to be able to process the incoming data and transform the data into a format
that was then stored on disk.  The protocol was defined such that I could be able to handle any upgrades
to the DMS switch protocol.  The protocol was designed such that any changes to the data structure will
only include the addition of fields and not removal of fields.  The reader application needed to be
designed such that any protocol changes will not cause the application to fail.  I decided to then
implement this feature using an array of functions where each of the functions will extract different
information from the data that was sent by the DMS switch.

{% comment %}
TODO: Talk about the read_dms_data, prepare_dms_data, rpc service and working on the GUI client of the
system.  I also need to speak about using semaphores and mmap to share data between the prepare_dms_data
and the GUI client that the customers use to look at the data.  Talk about creating a tool for the
QA group to be able to test different features that the product was expected to produce.  They were
able to use the tool to generate the data that was then read by the GUI client.  While the rpc
implementation was used to query the Ingres Database for access to historial data
{% endcomment %}

## Non-work Experience

# C++

While, my first 6+ years was spent exclusively using the C programming language, the use of the C++ programming
language experience did not follow a similar path.  Most of my experience with the C++ programmig language was
within the confines of working concurrently with Java and C# though mainly with Java.  The bulk of my experience
using the C++ programming language was when I was working at Riverbed/Aternity.  That said, I have also used
the C++ programming language at Progress Software and CIBER.  While my experience with Veritech was short lived
since this was a startup that didn't progress fair.  I will then describe my experience with the C++ programming
language.

I started to use the C++ with Veritech while creating a video game framework using MFC.  The use of C++ within
this context wasn't much but it gave me chance to learn somewhat about the Microsoft MFC framework.

# Libraries

This section will describe the different libraries that I have used to develop the different products using
C/C++.



{% comment %}
Local Variables:
backup-inhibited: t
End:
{% endcomment %}
