# Airline-Reservation-System
Simulated a simple Airline Reservation System which involved accessing shared resources. 
In real life, there are travel agencies who try to reserve seats for their customers. 
When a customer asks for a seat from a specific flight, the agency checks if there is an empty seat in the aircraft and reserves it immediately (if there is any). 
A customer can reserve more than one seat if needed. 
Since there are a lot of travel agencies out there, the reservations will be done based on FCFS (first come, first served) strategy. 
Only one reservations can be made on a seat, so there will be no overbooking. 
There will be one thread per agency simulating the activities of that agency. 
When an agency thread is booking a seat, the rest will do busy waiting.
