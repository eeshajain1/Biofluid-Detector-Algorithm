# Biofluid-Detector-Algorithm

I have written this C code to be used with an arduino and a breadboard set up with 8 led lights.

The RGB sensor detects the amount of a green light in a given sample of water. 
The more green light is detected, the higher the toxicity of the fluid will be. 

This algorithm takes in the green RGB value, and depending on the value, turns a certain number of lights on. 

(If the water is not at all toxic, 0 led lights will 
be turned on. If the water is very toxic, all eight will be turned on. If there is a medium amount of toxicity then some
intermediate number of lights will be turned on)
