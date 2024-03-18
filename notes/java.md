---
layout: resume
title: Java
subtitle: General Notes
page-width: lg
---

__Table of Contents__

[Introduction](#introduction)\
[Java](#java)\
[JUnit](#junit)\
[Maven](#maven)\
[Gradle](#gradle)\
[IntelliJ IDEA](#intellij)

# Introduction {#introduction}

The following page will contain information about the Java Programming Language ecosystem.  We will look
at different topics in an adhoc order.  Some of the information will be cross referenced but it is hoped
that the information can be of use to others.

## Java {#java}

While the Java Programming Language is a general purpose language having some elementary knowledge is a good start.
Let start with a simple java class and explain what each section means.  The following Main class will be created
in the Main.java within the src/org/example directory.

```java
package org.example;

import static java.lang.System.out;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        int [] values = new int[100];
        Arrays.fill(values, 1);
        out.println("Hello, world!");
    }
}
```

The above Main class can be compiled using the following command:

```sh
$ javac -d classes src/org/example/Main.java
```

The class can then be run using the following command:

```sh
$ java -cp classes org.example.Main
Hello, world!
```

As can be seen above the created class just prints "Hello, world!" and exits.  We are now going to explain how the
Main class was defined and used.  One can also use the __CLASSPATH__ environment variable to execute the Main class.

```sh
$ export CLASSPATH=classes
$ java org.example.Main
```

Note that the above assumes that the java command is executed within the directory that contains the classes sub-directory.
This is only a requirement if you are using relative directories in the classpath.  If you use absolute path in the classpath
then you can execute the java command from any directory.  The example above also only includes a single directory.  The
java classpath can also include multiple directories and/or archives that contain the required classes.  These archives
are usually jar files that are added to the classpath.  For instance, assume we have a jar file named, bar.jar then
the classpath is defined like

```sh
$ java -cp classes:bar.jar org.example.Main
```

or

```sh
$ export CLASSPATH=classes:bar.jar
$ java org.example.Main
```

Again, replacing the relative path names with their absolute path names allow you to execute the java command from anywhere.

Let us start with the __package__ statement above is used to confine classes within a given silo.  This silo allows
one to create classes with the same name and it insures that they won't class with each other.  The package name also
has another function that is useful when creating and using Java classes.  This in relation to compiling and executing
the compiled classes.  The __javac__ compiler command executed with the -d &lt;top-level-directory&gt; option will 
create the org/example directory in the &lt;top-level-directory&gt; directory.  The compiler will generate a Main.class
file in the org/example directory.  This is the file that will be used when executing the __java__ command above.

Let us explain what is the significants of the other syntax in the java class file.  The first thing to notice is the
__import__ key word that is being used in the Main class.  There is the __import static java.lang.System.out;__ that
is used by the compiler that all references to the __out__ static field is a reference from the __java.lang.System__ class.
While the __import java.util.Arrays;__ import tells the java compiler that all reference to __Arrays__ is really a reference
to __java.util.Arrays__.  This basically makes it such that the code is less cluttered with fully qualified class names.

Let now turn to defining the class itself such that the java command can execute the requested java class.  The first
requirement when creating a java class is that the name of the class should coincide with the name of the .java file name.
Thus the creation of the Main.java file is required by the java compiler.

The next requirement is the definition of the Main class.  For this, the Main needs to be made accessible to the java run time.
This then requires that the class be made __public__.  The java command will look for the requested class which in our case
the __org.example.Main__ class.  The java runtime will then look for a standard entry point.  In this case, it will
look for the static public void main method that expects a String array parameter,
__static public void main(String[] args)__ method.  This static method is only required for an entry class.  This method
is not required by non-entry point classes.

Finally, let us look at the anatomy of a java class.  Here is a simple java class that will define the different 
methods and fields of a simple class below.

```java
package org.example;

public class Point {

    private int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() { return x; }
    public int getY() { return y; }

    public void setX(int x) { this.x = x; }
    public void setY(int y) { this.y = y; }
}
```

The above contains two fields, (x and y), a single constructor, and 4 instance functions.  When defining your class fields
you need to define their access.  The fields can then contain the following access.

| Type | Description |
| :--- | :---: |
| __private__ | These fields can only be accessed by the current class |
| __protected__ | These fields can only be accessed by the current class or any defined sub-class |
| __public__ | These fields can be accessed by anyone |
| &lt;blank&gt; | These fields can be accessed by class with the same package name |

The above definition is fairly obvious except for the __blank__ access.  This is something that I have personally
never needed use of but that is part of the java language specification.

Note that the above definitions is also the case for methods defined in the class.

One last note that java generates documentation that is package and class specific.  This documentation is located at
[Java JDK 21 Documentation](https://docs.oracle.com/en/java/javase/21/docs/api/index.html){:target="_blank"}.

## JUnit {#junit}

This section will describe how to use JUnit framework to create and run tests against your developed classes.  JUnit was
initially created by Erich Gamma and Kent Beck.  JUnit has evolved throughout the years and its latest incarnation is JUnit 5
which we will be describing in this section.

While JUnit 5 contains a really good [User Guide](https://junit.org/junit5/docs/current/user-guide/){:target="_blank"}.  We will
only give enough information here to get you started with this framework.  Let us then look at how we can create test for the
Point class above.

The first that one should consider when creating tests is that a good pattern to follow is to create the test class using the
same package as the class that you are testing.  Thus a test class for the Point can be defined as follow.

```java
package org.example;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

public class PointTest {

    @BeforeAll
    static void beforeAll() {
        ...
    }

    @AfterAll
    static void afterAll() {
        ...
    }

    @BeforeEach
    void beforeEach() {
        ...
    }

    @AfterEach
    void afterEach() {
        ...
    }

    @Test
    void testOne() {
        Point point = new Point(1,2);

        Asserions.assertEqual(point.getX(), 1);
        Asserions.assertEqual(point.getY(), 1);
    }

    @Test
    void testTwo() {
        Assertions.fail("This is a failed test");
        ...
    }

    // Helper methods.
    private Point create(int x, int y) {
        return new Point(x,y);
    }

    ...

}
```

The above test should offer enough to be able to get started when writing tests using the JUnit 5 framework.  The
JUnit 5 framework uses the Assertions methods to determine if the given tests are successful or not.  These methods
will generate an exception if the given conditional test is incorrect.  The generated exception will contain
information about the discrepency of the test by describing what is expected and what was the actual result.

We now explain how the anatomy of the above test.  The references with the preceeding @ sign are called annotations
and this is used by the JUnit framework to determine how those methods should be called.   The ones that contain
the __BeforeAll__ and __AfterAll__ annotations will be executed before and after __all__ test methods that have
been defined.  While the ones that contain the __BeforeEach__ and __AfterEach__ annotations will be executed before
and after __each__ defined test.  While the ones with the __Test__ annotations are actually the tests that will be
executed.  Finally, the above test class contains methods that are not called by the JUnit framework but that are
used by the test for whatever needs it is required.   This just shows that one doesn't need to only define methods
that are annotated with the JUnit framework annotations.

While the above JUnit annotations should suffice for someone that is starting to use the JUnit 5 framework.  There
are other annotations and assertions that one can use at the following
[JUnit Javadoc](https://junit.org/junit5/docs/current/api/){:target="_blank"} link.

## Maven {#maven}

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

While the pom.xml looks like the following.

```xml
<?xml version="1.0" encoding="UTF-8"?>

<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>

  <groupId>org.example</groupId>
  <artifactId>simple-example</artifactId>
  <version>1.0-SNAPSHOT</version>

  <name>simple-example</name>
  <!-- FIXME change it to the project's website -->
  <url>http://www.example.com</url>

  <properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    <maven.compiler.source>11</maven.compiler.source>
    <maven.compiler.target>11</maven.compiler.target>
  </properties>

  <dependencies>
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.11</version>
      <scope>test</scope>
    </dependency>
  </dependencies>

  <build>
    <pluginManagement><!-- lock down plugins versions to avoid using Maven defaults (may be moved to parent pom) -->
      <plugins>
        <!-- clean lifecycle, see https://maven.apache.org/ref/current/maven-core/lifecycles.html#clean_Lifecycle -->
        <plugin>
          <artifactId>maven-clean-plugin</artifactId>
          <version>3.1.0</version>
        </plugin>
        <!-- default lifecycle, jar packaging: see https://maven.apache.org/ref/current/maven-core/default-bindings.html#Plugin_bindings_for_jar_packaging -->
        <plugin>
          <artifactId>maven-resources-plugin</artifactId>
          <version>3.0.2</version>
        </plugin>
        <plugin>
          <artifactId>maven-compiler-plugin</artifactId>
          <version>3.8.0</version>
        </plugin>
        <plugin>
          <artifactId>maven-surefire-plugin</artifactId>
          <version>2.22.1</version>
        </plugin>
        <plugin>
          <artifactId>maven-jar-plugin</artifactId>
          <version>3.0.2</version>
        </plugin>
        <plugin>
          <artifactId>maven-install-plugin</artifactId>
          <version>2.5.2</version>
        </plugin>
        <plugin>
          <artifactId>maven-deploy-plugin</artifactId>
          <version>2.8.2</version>
        </plugin>
        <!-- site lifecycle, see https://maven.apache.org/ref/current/maven-core/lifecycles.html#site_Lifecycle -->
        <plugin>
          <artifactId>maven-site-plugin</artifactId>
          <version>3.7.1</version>
        </plugin>
        <plugin>
          <artifactId>maven-project-info-reports-plugin</artifactId>
          <version>3.0.0</version>
        </plugin>
      </plugins>
    </pluginManagement>
  </build>
</project>
```

While the above pom file contains what is required to build and test this simple example java application.
It currently uses the JUnit 4 framework instead of the latest JUnit 5 framework.  We will look at how to
update this to use JUnit 5 in the [Maven notes file](maven/).
The other information that needs to be mentioned is that the pom needed to be updated to be able to build and test this project.
The following properties needed to be updated.

- maven.compiler.source
- maven.compiler.target

They needed to be set to java version 8 or greater instead of the default version of 1.7 to be able to build and test this project.

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

## Gradle {#gradle}

[Gradle](https://gradle.org/){:target="_blank"} is a tool that simplies the building, testing, packaging
and deploying for different programming language projects like java, scala, kotlin, C++, Groovy and Swift
projects.

More to come...

## IntelliJ IDEA {#intellij}

[IntelliJ IDEA](https://www.jetbrains.com/idea/){:target="_blank"} is a very popular Java IDE from JetBeans.
It has many very useful features that allow Java developers to focus on what matters most, developing software.
The different features that this IDE offers are described one the
[JetBeans webite](https://www.jetbrains.com/help/idea/getting-started.html){:target="_blank"}.

    - How to open a maven project
    - How to convert an IntelliJ project into a Maven project
    - How to convert an IntelliJ project into a Gradle project
    - How to update a maven dependencies
