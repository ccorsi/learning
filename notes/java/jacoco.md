---
layout: resume
title: JaCoCo
subtitle: A Java Code Coverage Library
page-width: lg
---

__Table of Contents__

- [Introduction](#introduction)
- [JaCoCo Maven Plugin](#plugin)
    - [Prepare Agent](#prepare_agent)
    - [Check](#check)
    - [Report](#report)

---

# Introduction {#introduction}

The [JaCoCo](https://www.jacoco.org/jacoco/index.html){:target="_blank"} is a java code coverage library tool that
developers can use to determine how well their test coverage is performing.  This tool provides the ability to see
which line of code has been tested and which line of code hasn't.   The developer can then take this information
to create new tests that execute the line of code that hasn't been tested.  This tool can be used within a IDE like
eclipse and IntelliJ or build tools like gradle and ant.  In this note we will be looking how to use this tool
within the [Maven](https://maven.apache.org){:target="_blank"} ecosystem.

## JaCoCo Maven Plugin {#plugin}

The JaCoCo team provides a Maven plugin that makes it easier for maven projects to use the advantage of the JaCoCo
coverage tool.  This plugin provides all of the features that one can use when using the command line tool.  Let us
then start by describing how to integrate JaCoCo within a maven project.

```xml
<?xml version="1.0" encoding="UTF-8"?>

<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>

  <groupId>...</groupId>
  <artifactId>...</artifactId>
  <version>...</version>

  <name>...</name>
  <url>...</url>

  <properties>
    ...
    <jacoco.version>0.8.11</jacoco.version>
    ...
  </properties>

  <dependencies>
    <dependency>
      <groupId>org.junit.jupiter</groupId>
      <artifactId>junit-jupiter-engine</artifactId>
      <version>${junit.jupiter.version}</version>
      <scope>test</scope>
    </dependency>
  </dependencies>

  <build>
    <plugins>
      ...
      <plugin>
        <groupId>org.jacoco</groupId>
        <artifactId>jacoco-maven-plugin</artifactId>
        <version>${jacoco.version}</version>
        <executions>
          <execution>
            <id>default-prepare-agent</id>
            <goals>
              <goal>prepare-agent</goal>
            </goals>
          </execution>
          <execution>
            <id>default-report</id>
            <goals>
              <goal>report</goal>
            </goals>
            <configuration>
              <title>JaCoCo Example Report</title>
              <footer>JaCoCo Example Report Footer</footer>
              <formats>
                <format>HTML</format>
              </formats>
            </configuration>
          </execution>
          <execution>
            <id>default-check</id>
            <goals>
              <goal>check</goal>
            </goals>
            <configuration>
              <rules>
                <rule>
                  <element>BUNDLE</element>
                  <limits>
                    <limit>
                      <counter>COMPLEXITY</counter>
                      <value>COVEREDRATIO</value>
                      <minimum>0.60</minimum>
                    </limit>
                  </limits>
                </rule>
              </rules>
            </configuration>
          </execution>
        </executions>
      </plugin>
      ...
    </plugins>

    ...
</project>
```

If you are not familiar with maven you can take a look at the [Maven](https://maven.apache.org){:target="_blank"}
web site or at my current set of Maven notes at [Java notes](../#maven) or [Maven notes](../maven).  While those
references are maven specific we will expand on what the above means and how this can be configured.

The first to notice is that the JaCoCo plugin is executed within three different goals, **prepare-agent**,
**report** and **check**.  Each of these goals are required to be able to properly use JaCoCo within your maven
project.  The **prepare-agent** goal is used to setup the JaCoCo command that will instrument the project java
classes.  This means that the java classes will be enhanced with JaCoCo specific code that is used to gather
metrics that will be stored and used to determine your code coverage.  The **check** goal is used to compare the
gathered information of your test runs and compare the data with the expected conditions defined in the **rules**
section above.  If those rules have not been fulfilled then the build will fail, by default.  While the
**report** goal is used to generate a user readable report that will contain information about the coverage
results of your maven project test runs.

### Prepare Agent {#prepare_agent}

The **prepare-agent** goal is necessary for the JaCoCo code coverage to work properly.  Without this setting any
of the subsequent plugin setup will be in vain.  The JaCoCo goal instruments the generate project class files with
JaCoCo specific calls which will be used to gather different metrics that will be compared with the defined rules
that you setup for the check goal above.  The concept of instrumenting a class file is the act of injecting of java
byte in the generated java class file.  The JaCoCo code coverage library doesn't change the functionality of the
project java classes but it just injects itself stragetically such that it can gather information that it can then
compare against.

Note that the above information is not required for understanding on how to use the JaCoCo code coverage library.
It is only to clarify the need to include the above goal to properly be able to use the JaCoCo code coverage library.

### Check {#check}

The **check** goal is where all of the work happens since this is the goal that the JaCoCo code coverage library
uses the gathered information to determine if the test coverage satifies the defined rules of the configuration
setting of the **check** goal.  The addition of this goal is to define what you want to insure that your tests
are covering.  Recalling that the **check** goal has the following settings.

```xml
          ...
          <execution>
            <id>default-check</id>
            <goals>
              <goal>check</goal>
            </goals>
            <configuration>
              <rules>
                <rule>
                  <element>BUNDLE</element>
                  <limits>
                    <limit>
                      <counter>COMPLEXITY</counter>
                      <value>COVEREDRATIO</value>
                      <minimum>0.60</minimum>
                    </limit>
                  </limits>
                </rule>
              </rules>
            </configuration>
          </execution>
          ...
```

The above configuration contains a single rule that we are going to be checking when you've finished running the
tests.  It defines the **element** tag that is used to determine what you want to compare.  In this case it is set
to **BUNDLE** which means that we are looking at the whole project classes.  There are other element type that you
can set when creating a rule. These are mentioned at the following
[JaCoCo check page](https://www.jacoco.org/jacoco/trunk/doc/check-mojo.html){:target="_blank"}. 

Upon selecting which element value you selected.  You then can create one or more limit that you want JaCoCo code
coverage tool checks when running the check target.  The limit defined above will check the total coverage of the
complexity counters such that it covers at least 60% of the code path of all the project classes combined.

While the above is a specific example on how you can define a particular check.  There are other options that you
can set and this information can be found on the
[JaCoCo Maven Check](https://www.jacoco.org/jacoco/trunk/doc/check-mojo.html){:target="_blank"} page.  Specifically
the [rules](https://www.jacoco.org/jacoco/trunk/doc/check-mojo.html#rules){:target="_blank"} section.

### Report {#report}

Let us finally look at the **report** goal for the JaCoCo code coverage tool.   This goal is executed by the maven
**site** target.  This goal will generate a use readable files from the gathered metrices from the test runs.
This will generate human readable data in xml, cvs or html.  These files will be located with the target/site/jacoco
sub-directory in the top-level maven project.

Let us now look at the settings in our pom above.

```xml
          ...
          <execution>
            <id>default-report</id>
            <goals>
              <goal>report</goal>
            </goals>
            <configuration>
              <title>JaCoCo Example Report</title>
              <footer>JaCoCo Example Report Footer</footer>
              <formats>
                <format>HTML</format>
              </formats>
            </configuration>
          </execution>
          ...
```

The above settings states that the generated human readable data should in be in html instead of all three formats of
xml, cvs and html.  Note that at this time, (version 0.8.11), those are only three formats that the tool currently
supports.  The generated html pages will be avaliable at target/site/jacoco/index.html within the top-level project
directory.  This will contain information about which files contained metrices and it also offers information on
which part of your code was covered by your tests and which weren't.  This is very useful to determine which part
of the code needs tests.

There is also the title and footer tags that basically are used a display text that will be shown on the generated
html web pages in the above case.

While the above offers enough information for one to get started with the **report** goal.  You can find more options
on the [JaCoCo Maven Report](https://www.jacoco.org/jacoco/trunk/doc/report-mojo.html){:target="_blank"} page.

While the above information should suffice to be able to get yourself aquainted with JaCoCo code coverage maven plugin
tool.  You can always learn more about the tool itself at
[JaCoCo Code Coverage Library](https://www.jacoco.org/jacoco/index.html){:target="_blank"} web page.
