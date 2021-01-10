# meta-ppgInteraction
yocto BSP layer developer for interacting with a ppg sensor and give the user his hearth rate (CDD + APP recipes).

Content
============

app_recipe \
cdd_recipe \
(respectively to implement the application interface and the sensor device driver).

Dependencies
============

No dependencies

Patches
=======

Please submit any patches against the meta-ppgInteraction layer through the github issue section of this repository.

Maintainer: https://github.com/alessandrolandra

Adding the meta-ppgInteraction layer to your build
=================================================

First of all you need to clone this repository (or download and copy the whole meta-ppgInteraction directory) into **your poky folder**. \
Then, after initializing your environment with
`source oe-init-build-env <your_build_path>`,
you have to add this layer to the image configuration by running:
```
bitbake-layers add-layer <your_poky_folder>/meta-ppgInteraction/
```
(In alternative you can add a line in <your_build_path>/conf/bblayers.conf file, reporting "<your_poky_folder>/meta-ppgInteraction" inside the BBLAYERS string).

Finally, to add the newly create recipes to the image to be deployed, you have to edit <your_build_path>/conf/local.conf file by adding the following lines: 
```
IMAGE_INSTALL_append = " hearthmonitor ppgreader"
KERNEL_MODULE_AUTOLOAD += "ppgreader"
```

You can now build the new image. \
If you are using a console only version, like the one that I used, the needed command is:
```
bitbake console-image
```
You can also use this layer in other architectures, foer example another raspberry pi model or qemuarm etc. \
All you need to do, in order to make these recepies compatible, is to change the COMPATIBLE_MACHINE in meta-ppgInteraction/recipes-ppg/cdd_recipe/ppgreader.bb. For example: \
```
#COMPATIBLE_MACHINE = "raspberrypi4"
COMPATIBLE_MACHINE = "qemuarm"
```
Finally, you probably need to change the image to build, for example using `bitbake core-image-minimal`.
