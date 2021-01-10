# meta-ppgInteraction
yocto BSP layer developed for interacting with a ppg sensor and giving the user his hearth rate (CDD + APP recipes).

Content
============

app_recipe \
cdd_recipe \
(respectively to implement the application interface and the sensor device driver).

Target machine
============

raspberry pi 4
(see compatibility note at the end (`*`))

Patches
=======

Please submit any patches against the meta-ppgInteraction layer through the github issue section of this repository.

Maintainer: https://github.com/alessandrolandra

Adding the meta-ppgInteraction layer to your build
=================================================

The following instructions are supposed to be executed in an environment equipped with Poky, as reference distribution of the Yocto Project. \
\
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
(`*`) This layer may probably also work on other architectures (other raspberry pi model, qemu etc), but probably some timing differencies must be taken into account in the app_recipe. \
I succeeded in making this working with the qemuarm machine; \
all you need to do, in order to make these recepies compatible, is to change the COMPATIBLE_MACHINE in **meta-ppgInteraction/recipes-ppg/cdd_recipe/ppgreader.bb**:
```
#COMPATIBLE_MACHINE = "raspberrypi4"
COMPATIBLE_MACHINE = "qemuarm"
```
The timing change that I was mentioning before, for my qemuarm machine, was to change the line 69 in the **meta-ppgInteraction/recipes-ppg/app_recipe/files/hearthmonitor.c** file from this:
```
usleep(17000);
```
to this:
```
usleep(17000);
```
