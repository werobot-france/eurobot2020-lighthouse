# Eurobot2020 lighthouse

This repository hold the code used by lighthouse in the eurobot2020 contest by the werobot team.

This code consist of the arduino .ino sketch used to programm the arduino nano.

## Behaviour

This code implement the following behaviour:

When a activation switch is pressed the code will step by step change the angle of the first then of the second servo.

The step by step deployment (kind of a animation behaviour) is needed to avoid the too quick direct deployment.

One by one the two arms are deployed until they reach their final positions.

After the deployment we can turn on the light or light beam.

## Ideas/TODO

Make a arming button with a arming status led.

With this idea we can install the arduino without accidently deploy the device and then arm the lighthouse to prepare a future deployment.
