# Welcome

The intent of this repository is to provide a single repository where I can teach myself something I'm interested in
learning.  This can be anything from programming languages, algorithms, package/libraries, new features, etc.  It will
contain different branches for each of the different projects that will be worked on.  The intent is to have this file
list the different projects within this repository.  Thus I will list the different project/branches that are part of
this repository with some description about the status of those branches.


| Branch | Description | Status |
| --- | --- | --- |
| base | Initial created as a starting point for subsequent branches | inactive |
| cpp_data_structs_and_algos | Solutions to Techie Delight Programming Challenges in C++ | active |
| cpp | Odd and even C++ code doodling code | inactive |
| dataloader | Data Loader Template Class for populating instance in C++ | active |
| docs | Source to my https://ccorsi.github.io/learning web site | active |
| gh-pages | Original source to the above web site | inactive |
| menucli | Command Line Menu written in Python, project moved to [menucli](https://github.com/ccorsi/menucli) | inactive |
| multiversion-jar | Simple java jar example that uses jar feature to incorporate different java version class implementation | inactive |
| plogger | Java agent used to log input to java instance classes | inactive |
| plogger4j | Initial implementation of the plogger | inactive |
| python-machine-learning | Implementation of the Machine Learning | inactive |
| timetrackerplugin | Firefox/Chrome time tracking plugin | inactive |

While the above list offers an overview of each branch.  They don't offer more
information than that.  I will then offer some more information about those
branches in hopes that some would find that information useful.  Yet, I won't
describe each branch since some of these branches will probably disappear since
they don't offer any benefits keeping them around.

The [cpp_data_structs_and_algos](https://github.com/ccorsi/learning/tree/cpp_data_structs_and_algos)
branch was initially started to learn how to program in C++ by solving the
different programming challenges that are part of the
[Techie Delight](https://www.techiedelight.com/) web site.  This effort
evolved by teaching myself how to use CMake, CTest, GoogleTest and different
C++ features.  This has allowed me to become more comfortable using the above.
I've had an oppurtunity to learn how to use CMake with CTest.  The main thing
that I have come to appreciate is the learning and using of GoogleTest.  I
am a proponent of testing your software.  It provides confidence in your code
and makes one more daring with making changes to the code without fear.

The [dataloader](https://github.com/ccorsi/learning/tree/dataloader) branch was started because of the effort that I have put
into the cpp_data_structs_and_algos branch.

The [doc](https://github.com/ccorsi/learning/tree/doc) branch was started because I wanted to learn how to create and web site using GitHub Actions.

The [menucli](https://github.com/ccorsi/learning/tree/menucli) branch was created because of my work on the python-machine-learning branch.  I wanted to create a shell like menu that I can use to choose which machine learning implementation I would like to run.  The command line menu became useful and provided the flexibilty that I was looking for.  This work then lead me to move this code into its own repository called [menucli](https://github.com/ccorsi/menucli/).

The [multiversion-jar](https://github.com/ccorsi/learning/tree/multiversion-jar)
branch was created to just practically implement and test how to create a jar
file that contains version specific classes using the multi-release feature of
the jar specification.

The [plogger](https://github.com/ccorsi/learning/tree/plogger) branch was
created to produce a java agent that will log what parameter values have
been passed to a class function.  This also includes the constructor of a
class.  This was just something that I wanted to recreate that I did at a
former company that I use to work for.  There is interest in creating a
similar agent but this time in C/C++ that performs a similar task as what
was implemented in this branch.

The [python-machine-learning](https://github.com/ccorsi/learning/tree/python-machine-learning)
branch was created from the work that I had initially done on repit.  This
is basically the code that was transfered from that web site to GitHub.
This work was what generated the menucli branch and separate repository.
It was created by me to implement the different machine learning
implementations from the Python Machine Learning book by Sebastian Raschka and
Vahid Mirjalili.

The [timetrackerplugin](https://github.com/ccorsi/learning/tree/timetrackerplugin) branch was created because I wanted to track how
much I spend on different web sites during the day.  I then decided to look
into how one can go about doing this within FireFox.  I then noticed that the
same set of code also works within Chrome.  The initial work perform was able
to track the times that I was spending on each web page.  This was initial
work was exciting since it did give me an idea where I spend my time.  I
stopped working on this because of my lack of creativity with create web
pages.  I do intend to come back to this project with the hope of being able
to add the missing web page interface that will make this project useful for
others besides myself.
