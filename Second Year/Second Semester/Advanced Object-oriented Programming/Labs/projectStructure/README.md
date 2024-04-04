# Sample project
This is a sample project that outlines one way to structure the classes, 
when extensibility and maintainability are kept in mind.

## model
This package contains the list of entities that are used through the 
application. The classes within are simple POJOs (Plain Old Java 
Objects, meaning classes that just have private fields, getters and 
setters, constructors and any of the general use methods needed: 
toString, equals, hashCode, compareTo(T), etc). 

## exceptions
The list of custom exceptions used in the application.

## persistence
### GenericRepository
This is a generic contract (interface) that any repository (or DAO) 
needs to implement in order to be useful within this application. If
a particular repo needs custom methods, they can be defined in the 
implementing class.

### concrete repositories (Eg. Entity1Repository)
These are the actual implementations of the Repos (or DAOs). They 
include only actions that work with the corresponding entity. Usually,
there is a 1-to-1 relation between the entities and repositories.

## services
These are the main functionalities available in the application. 
If multiple functionalities refer to the same area, they can be 
grouped in the same service. Services will make use of any related
repository they need, so we can have services with no, one or multiple
repositories. The services should not have any interaction with any 
input/output interface (Eg. should not read or write from/to the 
console).

## view
Here we can group any classes that have direct interaction with the 
user and connect his input/output to the services within the 
application. 
