---
layout: resume
title:
subtitle:
css: "/assets/css/resume.css"
---

### *Profile*
<hr>

Seasoned Software Engineer with 25+ years of experience developing complex server-side and client-side software products from design through implementation using
mainly Java and C/C++.  Experienced in all other aspects of the software development process including scheduling, maintaining, presenting, mentoring, debugging
and documenting.

### *Technical Skills*
<hr>

***Languages***: Java, C/C++, C#, Python, Groovy, Perl, Ruby, JavaScript  
***Frameworks***: Mockito, PowerMock, JUnit, BCEL, ASM, Camel, RMI, JNDI, JDBC, JAXP, XML, XSLT, DOM, SAX, JNI, EJB, Servlet, JSP, JTA, JMS, JMX  
***Developer Tools***: Git, Docker, Visual Studio, Eclipse, Netbeans, IntelliJ, Emacs, XCode, Mercurial, Subversion, Ant, make, maven  
***Application Servers***: Weblogic Server, WebSphere Application Server, Tomcat, JBoss AS, ActiveMQ, Jetty  
***Operating Systems***: Windows, Linux, Mac OS X, FreeBSD, Solaris, SunOS, AIX  
***DBMS***: Oracle DBMS, MySQL, MSSQL, PostgreSQL, MongoDB  
***Office Tools***: Microsoft Office, Google Office Suite  

### *Experience*
<hr>

| Member of the Technical Staff | 2012-2020 |
| :--- | ---: |
| Riverbed Technology/Aternity LLC | Cambridge, MA |
  
- Part of the team that implements and maintains the Java and .NET{CORE} instrumentation agents used for Application Performance Monitoring (APM)
  - _Java Agent_: Responsible for several part of the different agent features that are used throughout the code.  This included changes within the native layer which is written in C++
  - _.NET Agent_: Responsilbe for some part of the different agent features that are used throughout the code.  This also included changes within the native layer which is written in C++
- Initiated, architected and the main implementer of the Java agent new bytecode instrumentation. Replacing the original java bytecode instrumentation logic as part of the next phase of our java agent bytecode manipulation
  - Replaced all original Java injection code with newly defined Java classes that implemented original injected code features.
	- This include the porting the original tests to conform to the new mechanism.  The transformed tests were compared to the original test results to insure consistency between the two implementation.
	- Newly created tests were added that tested the features that where not part of the original code to insure that the injected code was performing as expected.
  - Replaced original byte code instrumentation code base, (written in C++), that injects the new byte code mechanism which uses the new injected class code
- Replaced internal process to reduce ClassCircularityError issues
  - The original code would generate ClassCircularityError issues in certain cases, applied several changes that reduced the prospect of producing this exception
- Removed internal limitation for adding special instrumentations
  - Updated the C++ and Java layer to remove the limitation of 64 special instrumentation within our Java agent
- Worked on implementing several instrumentation features for our Java and .NET{CORE} instrumentation agents
  - For example, the ability to instrument MangoDB on .NET
- Enhanced method parameter reporting to be able to pinpoint which field within objects should be recorded
  - 
- Implemented and improved concurrency access to several internal structures used by our instrumentation agents
- Collaborated with the integration of Docker within our product and build process
- Created, documented and presented major implementations of our instrumentation agent product
   - Documented and presented the new java agent injection process to the team
   - Documented and presented the new method paramter reporting features that were added
- Mentored junior members of the group
- Interfaced with customers and solution engineers to resolve and improve the use of the product
    - Worked on several Proof of Concept issues with our solution engineers
    - Worked with our technacial support engineers to resolve issues with our products that our clients faces
    - These issues included fixing bugs, clarifying how the code works, suggesting work arounds and in some cases explaining how and why certains issues were caused by third party software
- Worked with or extended our integration with Spring, JDBC, JMS, EJB, Axis, Netty, Vertx, WebSphere Application Server, Oracle WebLogic Application Server, Tomcat, Jetty, MongoDB and others
- Converted the Classic Jenkins build process to Jenkins pipeline feature
- Used Java, C++, C#, Python, Groovy, git, Jenkins, Docker, Ant, Ivy, Maven, Archiva, Nexus and others to develop and support our instrumentation agents for Java and .NET{CORE}
  
| Principal Software Engineer  | 2008 - 2009 |
| :--- | ---: |
| Progress Software Technology | Bedford, MA |
  
- Primary developer for the ObjectStore&#174; Java Middle Tier Library (JMTL), a highly scalable middle-tier caching &amp; transaction management system.  Responsibilities included design, implementation, scheduling, mentoring, testing, and documentation
    - _Updated JMTL integration with most prominent EJB servers_ such as Weblogic and JBoss using technologies such as JTA and XAResource
	- Provided a standard based implementation of one and two phase commit processes for the JTA XAResource implementation
    - _Designed and implemented new features_ in JMTL such as real-time counter updates and run-time management tool
    - _Resolved major bugs_ within the JMTL update of JTA XAResource integration such as inconsistent committing/abort between ObjectStore transactions and application server XAResource transaction callbacks
    - _Assisted  technical support concerning critical issues_ using ObjectStore&#174; JMTL for customers such as NIST
- Contributing member of development team for ObjectStore, the leading Object-Oriented Database Management System
    - _Designed and implemented new feature_ in OSJI such that C++ real-time counter updates can be performed within OSJI java layer using JNI
    - _Updated endgame testing scripts_ such that OSJI 64-bit testing is properly setup and executed by the testing engineers
  
| Technical Support Engineer | 2011 - 2012 |
| :--- | ---: |
| FUSE Source | Bedford, MA |
  
- Responsible for the technical support, finding and fixing bugs for the ActiveMQ/Message Broker, ServiceMIX/ESB, Camel/Message Router and CXF/Service Framework products
- Created different patches for ActiveMQ, Camel, karaf and osp4j pax-logging projects that have been applied
- Helped customers on how to best use the product by giving advice and creating working examples that they can use as a starting point
- Developed a simple ruby script that has helped improve our front-end services. This has allowed these systems to become stable when prior to this change these systems required constant attention
- Lead the bug queue process with engineering
- Part of the 24/7 support rotation for 24/7 production support for customers
  
| Principal Software Engineer | 2008 - 2009 |
| :--- | ---: |
| Progress Software Technology | Bedford, MA |
  
- Primary developer for the ObjectStore&#174; Java Middle Tier Library (JMTL), a highly scalable middle-tier caching &amp; transaction management system.  Responsibilities included design, implementation, scheduling, mentoring, testing, and documentation
    - _Updated JMTL integration with most prominent EJB servers_ such as Weblogic and JBoss using technologies such as JTA and XAResource
    - _Designed and implemented new features_ in JMTL such as real-time counter updates and run-time management tool
    - _Resolved major bugs_ within the JMTL update of JTA XAResource integration such as inconsistent committing/abort between ObjectStore transactions and application server XAResource transaction callbacks
    - _Assisted  technical support concerning critical issues_ using ObjectStore\texttrademark JMTL for customers such as NIST
- Contributing member of development team for ObjectStore, the leading Object-Oriented Database Management System
    - _Designed and implemented new feature_ in OSJI such that C++ real-time counter updates can be performed within OSJI java layer using JNI
    - _Updated endgame testing scripts_ such that OSJI 64-bit testing is properly setup and executed by the testing engineers
  
| Principal Software Engineer | 2007 |
| :--- | ---: |
| Emptoris | Burlington, MA |
  
- Lead developer responsible for maintaining and enhancing Intelligence Attributes (IA) and IF Java-based frameworks used by other teams within the organization as a basis for several of Emptoris' commercial products
  

| Senior Software Engineer | 2000 - 2006 |
| :--- | ---: |
| Progress Software Technology | Bedford, MA |
  
- Primary developer for the ObjectStore&#174; Java Middle Tier Library (JMTL), a highly scalable middle-tier caching &amp; transaction management system.  Responsibilities included design, implementation, scheduling, mentoring, testing, and documentation
    - _Integrated JMTL with most prominent EJB servers_ such as WebSphere, Weblogic, JBoss and Sun Application Server, using technologies such as JTS, JTA and XAResource
    - _Designed and implemented new features_ in JMTL such as object pooling mechanism, extent implementation, integration with two phase object locking mechanism, and its associated byte-code enhancement tool
    - _Created design documents in order to schedule and mentor_ other group members on implementation of feature enhancements such as two phase object locking byte-code enhancer tool and JMTL proxy code generator
    - _Enhanced existing features_ within JMTL such as the internal profiling feature, Console Swing tool, Virtual Transaction Manager, Virtual Transaction Manager Management tool
    - _Resolved major bugs_ within the JMTL transaction Manager such as inconsistent committing/abort between ObjectStore transactions and application server XA transactions
    - _Enhanced product build_ for JMTL by replacing makefiles with Ant build scripts
    - _Updated examples that ship with the product_, such as EJB server examples, JMTL Servlet/JSP example for use with Tomcat and JMTL-specific Ant tasks
    - _Assisted consultants with issues concerning the usage and best practices_ using ObjectStore JMTL for customers such as Starwoods, Sakonnet, and Lockheed Martin
- Contributing member of development team for ObjectStore, the leading Object-Oriented Database Management System
    - _Contributed to development_ of a change-log mechanism for a Data Source Synchronization product (DSS) used to automatically synchronize data between ObjectStore and Oracle or MySQL
    - _Architected and designed testing process and framework_ using JUnit, then became go-to person to facilitate adoption of this framework within the ObjectStore Java group
    - _Contributed enhancements and performance improvements_ to the ObjectStore Java Interface (OSJI)
  
| Developer Support Engineer | 1998 - 2000 |
| :--- | ---: |
| Progress Software Technology | Bedford, MA |
  
- _Responsible for technical support as well as finding and fixing bugs_ in ObjectStore &amp; JMTL
- _Trained and certified consulting group and support members_ on building and using purify with the ObjectStore product
- _Mentored others_ on using non-ObjectStore tools such as Visual C++, ClearCase, snapshot system, debuggers, etc
- _Worked on integration of our Java product_ with Sybase Jaguar EJB Server
- _Obtained Sourcesmart certification_ on Solaris and WinNT
- _Handled critical customers_ such as MarketXT, Fairmarket and Smith Barney, including emergent on-site troubleshooting
  

| Consultant (assigned to First Data Corporation) | 1998 |
| :--- | ---: |
| CIBER | Boston, MA |

- Responsible for development on middle-tier of an application using C/C++ and Visual C++
    - Server application used sockets, threads and MSSQL to process requests
    - Requests were to a mainframe, which were received from a Web application
- Implemented new API for the Web application to process requests to the mainframe
- Enhanced application that retrieves data from the mainframe to populate an MSSQL database by replacing large and complex switch statements with a simple array of generic function pointers which streamlined their use of DLLs
- Added GUI feature for parsing data files to populate combo boxes
- Implemented support for seamless handling of Y2K and non-Y2K clients
- Responsible for fixing bugs uncovered by QA department, using Visual Source Safe for tracking changes
- Enhanced debugger tool used to check that implemented server API calls work properly
  
| Consultant | 1994 - 1998 |
| :--- | ---: |
| Bell Sygma | Montreal, Quebec, Canada |
  
- Developed an application to parse raw data from a DMS switch and store it in both a database and a shared memory cache so that GUI clients could make both real-time and historical queries against it.  Included the following components:
    - Back end interpreter of raw DMS data to be displayed at GUI client and stored in database
    - IPC communication layer between GUI client and DMS data interpreter
    - Client/server interface to generate embedded SQL queries using parameters specified via RPC
- Enhanced GUI client end of a real-time application by adding new features and making it internationally viable, using Neuron Data's Open Interface in C on UNIX
- Developed general library functions used throughout a real-time client/server application in C using object-oriented concepts
- Lead developer of back end program for intranet project, using C, embedded SQL and Ingres
    
| Programmer | 1994 |
| :--- | ---: |
| Veritech | Montreal, Quebec, Canada |
  
- Designed and implemented the preliminary structure of a video game using MFC/C++ on Windows
    
| Programmer Analyst | 1992 - 1994 |
| :--- | ---: |
| Ranmar Business System | Montreal, Quebec, Canada |
  
- Primary author of a GUI terminal emulation program using C and Windows SDK, which consisted of a protocol that dynamically generated client side windows based on properties specified on the server side
- Enhanced GUI library to support dynamic generation of windows
- Created new feature for financial and rating software package to allow users to view/edit client records, using C on UNIX
  

### *Education*
<hr>
  
| ***Concordia University*** | Montreal, Quebec, Canada |
| :--- | ---: |
| _Bachelor of Science, Specialization in Applied Mathematics, Minor in Computer Science_ | _May 1992_ |


{% comment %}
Local Variables:
backup-inhibited: t
End:
{% endcomment %}
