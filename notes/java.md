---
layout: resume
title: Java
subtitle: General Notes
page-width: lg
---

# Introduction

The following page will contain information about the Java Programming Language ecosystem.  We will look
at different topics in an adhoc order.  Some of the information will be cross referenced but it is hoped
that the information can be of use to others.

## Maven

[Maven](https://maven.apache.org/){:target="_blank"} is a tool that simplifies the building, testing,
packaging and deploying of java projects.  It encapsulates that work within a fairly simple xml file
named pom.xml.  This file contains all of the information required to work with your project.  The
beauty is that you have the ability to pick and choose which third party packages you would like to
use within your project.  Maven will get those required packages and automatically apply them to
your build process.

I will give a overview of how to use Maven to build a fairly straight forward java project that only
requires some packages to needed to build, test and run.  More information will be located within a
seperate [Maven](maven/) documentation.  This will contain more information about how to use Maven
and should be helpful for someone that wants to take a bigger step using Maven to build their project.

We thus shall start with downloading the latest version of Maven which is located at the following
[Maven download](https://maven.apache.org/download.cgi){:target="_blank"}.  After expanding the
operating system archive file.  You need to insure that the bin directory of your maven top-level
directory is part of your path.  You will also need a version of java installed on your system.  Maven
will be able to use the one that is part of your path or it will use the one that is defined for
the JAVA_HOME environment variable.  You can then check if maven was properly configured by running
the following command:

```shell
$ mvn --version
Apache Maven 3.6.3 (cecedd343002696d0abb50b32b541b8a6ba2883f)
Maven home: C:\tools\maven\3.6.3
Java version: 20.0.1, vendor: Oracle Corporation, runtime: C:\tools\java\jdk\openjdk\20
Default locale: en_US, platform encoding: UTF-8
OS name: "windows 10", version: "10.0", arch: "amd64", family: "windows"
```

Now that we have maven properly installed on your system we can then look at creating a simple maven
project from the command line.  Maven offers the concept of plugins that can be used within a maven
project.  Plugins can be created for different uses and one of them is to create new maven projects.
These type of plugins are called archetypes that will create a maven project using the following
command:

```shell
$ mvn archetype:generate
```

While the above can be used to create a new maven project from a list of archetypes.  This is great
but the issue is that there are thousands of possible archetype to choose from.  We will then show
how you can create a simple maven project using the following command:

```shell
$ mvn archetype:generate -DarchetypeGroupId=org.apache.maven.archetypes -DarchetypeArtifactId=maven-archetype-quickstart
[INFO] Scanning for projects...
[INFO]
[INFO] ------------------< org.apache.maven:standalone-pom >-------------------
[INFO] Building Maven Stub Project (No POM) 1
[INFO] --------------------------------[ pom ]---------------------------------
[INFO]
[INFO] >>> maven-archetype-plugin:3.2.1:generate (default-cli) > generate-sources @ standalone-pom >>>
[INFO]
[INFO] <<< maven-archetype-plugin:3.2.1:generate (default-cli) < generate-sources @ standalone-pom <<<
[INFO]
[INFO]
[INFO] --- maven-archetype-plugin:3.2.1:generate (default-cli) @ standalone-pom ---
[INFO] Generating project in Interactive mode
[INFO] Archetype [org.apache.maven.archetypes:maven-archetype-quickstart:1.4] found in catalog remote
Define value for property 'groupId': org.example
Define value for property 'artifactId': simple-example
Define value for property 'version' 1.0-SNAPSHOT: :
Define value for property 'package' org.example: :
Confirm properties configuration:
groupId: org.example
artifactId: simple-example
version: 1.0-SNAPSHOT
package: org.example
 Y: :
[INFO] ----------------------------------------------------------------------------
[INFO] Using following parameters for creating project from Archetype: maven-archetype-quickstart:1.4
[INFO] ----------------------------------------------------------------------------
[INFO] Parameter: groupId, Value: org.example
[INFO] Parameter: artifactId, Value: simple-example
[INFO] Parameter: version, Value: 1.0-SNAPSHOT
[INFO] Parameter: package, Value: org.example
[INFO] Parameter: packageInPathFormat, Value: org/example
[INFO] Parameter: package, Value: org.example
[INFO] Parameter: groupId, Value: org.example
[INFO] Parameter: artifactId, Value: simple-example
[INFO] Parameter: version, Value: 1.0-SNAPSHOT
[INFO] Project created from Archetype in dir: C:\projects\java\maven\simple-example
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  25.154 s
[INFO] Finished at: 2024-03-12T18:36:32-04:00
[INFO] ------------------------------------------------------------------------
```

The completion of the above will then generate the following files with the simple-example
directory.

```
pom.xml  src/

simple-example/src:
main/  test/

simple-example/src/main:
java/

simple-example/src/main/java:
org/

simple-example/src/main/java/org:
example/

simple-example/src/main/java/org/example:
App.java

simple-example/src/test:
java/

simple-example/src/test/java:
org/

simple-example/src/test/java/org:
example/

simple-example/src/test/java/org/example:
AppTest.java
```

You can then build, test and package the above maven project using the following commands:

```shell
$ mvn compile
$ mvn test
$ mvn package
```

The compile target will build the source files within the src/main sub-directory.  While the
test target will build and run the tests within the src/test sub-directory.  While the package
target will generate a jar file that contains the built files from the src/main sub-directory.

The above information should is a good starting point when using Maven but alas there are many more
options that one needs to know about Maven and this will be discussed further in its seperate
[Maven notes file](maven/).

## Gradle

[Gradle](https://gradle.org/){:target="_blabk"} is a tool that simplies the building, testing, packaging
and deploying for different programming language projects like java, scala, kotlin, C++, Groovy and Swift
projects.

More to come...

## IntelliJ IDEA

[IntelliJ IDEA](https://www.jetbrains.com/idea/){:target="_blank"} is a very popular Java IDE from JetBeans.
It has many very useful features that allow Java developers to focus on what matters most, developing software.
The different features that this IDE offers are described one the
[JetBeans webite](https://www.jetbrains.com/help/idea/getting-started.html){:target="_blank"}.

    - How to open a maven project
    - How to convert an IntelliJ project into a Maven project
    - How to convert an IntelliJ project into a Gradle project
    - How to update a maven dependencies
