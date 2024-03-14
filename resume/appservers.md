---
layout: resume
title: Application Servers
subtitle: What I know
cover-img: "/assets/img/gratisography-224H-free-stock-photo.jpg"
---

# Introduction

Here I will be discussing my knowledge of the different application servers that I have used in and out of a
working environment.  The different type of application servers used range from web servers to full fledge
application servers.  I will then discuss each type in turn and offer information on when and in what capacity
those servers have been used.

# Web Servers

The use of web servers has grown throughout the years, the main features of these servers is to manage web activities.
While there are and have been many products to choose from here. I have had the oppurtunity to work with Apache HTTP
server, Tomcat, Jetty and IIS.  I will then disucss my knowledge and experience with each of these servers.

## Apache HTTP Server

While Apache HTTP Server is one of the most popular web server in the world.  My experience with this product has been
limited to hosting test results access from our products unit and system tests.  This need came about because our unit
and system tests where not being kept beyond the next test run.  This required that I grab all of the relavent test data
from one or more product runs and place them within a directory structure that the Apache HTTP Server was hosting.  I
configure the Apache HTTP Server to be able to service these web pages.  While the generated pages was done outside of
me setting up the Apache HTTP Server.  The host was then used to look through the different test runs be it unit or 
system test results.

## Apache Tomcat

The Apache Tomcat web server is one of the products that I have used the most within a work environment.  This product was
used to test our integrations of our product with respect to Java specifications in which the Apache Tomcat server implements.
This required that I understood how to develop, deploy and run the different services that the Apache Tomcat web server
implements.  This has provided a good foundation of the different Java standards that are being used within the Apache
Tomcat server.  This includes the implementation and usage of Servlets and JSP.   While this is a small part of what the
Apache Tomcat server implements, I've had to also understand some of the internal implementations to be able to resolve
issues with our products integrations with respect to that Apache Tomcat server.  Those issues were specific to Apache Tomcat
server and were not relevant to other servers that implement the same specifications like Jetty.

## Jetty

The Jetty web server was also used extensively within the same context as the Tomcat web server.  I used this product to
insure that what worked with Tomcat was also working with Jetty.  The value of this product was that I was able to gain
more confidence that our integration of our product will work with the Servlet and Jsp specifications.

## IIS

While IIS is something that I have used within a working environment, my experience of using this web server is limited.
My use of IIS was more with just processing simple pages that did not use any of the Microsoft specific frameworks like
ASP .NET.  Which leads me to mention that my work experience and non-work experience is very limited.

# Application Servers

While my experience with using web servers has involved several different products.  My experience with application
servers has not been as broad but still involved several products.  I will discuss my knowledge of application
servers next.

The following sections will discuss my experience using the different application servers that I had to use within a
working environment.

## Oracle WebLogic Application Server

Oracle's WebLogic Application Server was one of the first application servers that I had to learn and use within a
working environment.  I needed to know how to use the application server different services.  These included the use of
Servlets and Enterprise JavaBeans.  This required the need to be able to create a configuration that would then be used
to deploy applications that were used to test our product against.  This required that I understand how the Orable
Application WebServer is configured for the applications that I needed to deploy.   

## IBM WebSphere Application Server

The IBM WebSphere Application Server is another product that I needed to understand how to use its Servlets and Enterprise
JavaBeans features.  This also include how to the Jsp implementation works.  This application server is the most complex
application server that I have had to work with.  I found that it took more time to come to understand the internals of
this application server to be able to integrate our product with.  It also required an understanding on how to configure
an instance to be able to deploy and test our product with.

## JBoss Application Server

JBoss Application Server is another application server that I needed to understand how to use Servlets and Enterprise JavaBeans.
This application server was also being used to test our product and I needed to be able to configure and run an instance of the
JBoss Application Server.  This required that I understand how to hook our product within this environment by understanding some
of the internals of the JBoss Application Server.  While this application server has been renamed to Wildfly.  I have not had
an oppurtunity to work with the later version.  I am fairly certain that the two application servers are similar except for the
fact that the newer version will contain features from the latest java enterprise specifications.

## GlassFish Application Server

The GlassFish application server was something that I have used within a working environment.  It is not a product that
I used as often as the WebLogic Application Server and the WebSphere Application Server.  This was based on the fact
that this application server was not something that our customers would use to develop and deploy their products on.  It
basically became another tools to test our product against.  The main advantage of this product is that it is the
reference implementation of the Java Enterprise Specifications.  This was then used to insure that our products was
still functioning correctly with the newer releases of the specifications.  It would give us a chance to enhance our
product with the new features that will eventually be implemented as path the WebLogic Applcation Server and WebSphere 
Application Server.  While its significance is not relevant to a production environment, its value was relevant to our
products evolution.  Thus, I had to understand how to configure and deploy our product within this application server. 
This afforded me the oppurtunity to gain experience with working with this application server.

# Other Types of Servers

While the above mentioned web and application servers are most of the servers that I have worked with.  They are not the only 
types of servers that I have worked with.  There are other servers that I have worked with, these include ActiveMQ, ServiveMIX
and other servers.  These servers implement a subset of the Java Enterprise Specifications, like JMS for ActiveMQ, or a different 
specification, like OSGi for ServiceMIX.  They nonetheless are servers that I needed to understand so that our product could
be integrated with these different products.

# Conclusion

While I've gain knowledge with many different web and application servers, this knowledge was mainly acquired within a
working environment.  Though this knowledge is not extensive because of the kind of work that I was doing.  It
nonetheless required that I learned how to integrate my product within these different servers.  This effort required
that I understand the internal aspects of the different products.  This has given me a greater appreciation of the different
servers that I have had an oppurtunity to work with.


{% comment %}
TODO: I should include the different application servers that I have worked with and
also application servers that I have also learned outside of a job environment.

The list of application servers that I have actually work with in a working environent
are:

	- Oracle WebLogic Server
	- WebSphere Application Server
	- Tomcat
	- Resin
	- Jetty
	- JBoss Application Server


The following application servers which I have used outside of a work environment are:

	- GlassFish
	- WildFly

Do I have any application server that I would be interested in learning?

	- IIS


Where does Apache http server within this section?   Should this be included or not?
It is more of a web server then an application server.  It is something that I have
used within a working environment to perform simple tasks but most of this time
this is something that has been setup by the IT department.

{% endcomment %}

{% comment %}
Local Variables:
backup-inhibited: t
turn-on-auto-fill
End:
{% endcomment %}
