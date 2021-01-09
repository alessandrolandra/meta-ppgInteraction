# meta-ppgInteraction
yocto BSP layer developer for interacting with a ppg sensor and give the user his hearth rate (CDD + APP recipes).

Content
============

app_recipe
cdd_recipe
(respectively to implement the application interface and the sensor device driver).

Dependencies
============

No dependencies

Patches
=======

Please submit any patches against the meta-ppgInteraction layer through the github issue section of this repository

Maintainer: https://github.com/alessandrolandra

Adding the meta-ppgInteraction layer to your build
=================================================

First of all you need to clone this repository and copy the whole meta-ppgInteraction directory into your poky folder.
Then, after initializing your environment with
'source oe-init-build-env <your_build_path>',
you have to add this layer to the image configuration by running
'bitbake-layers add-layer ../meta-ppgInteraction/'.
(In alternative you can add a line in conf/bblayers.conf file reporting "<your_poky_folder>/meta-pphInteraction" inside the BBLAYERS string).

Finally, to add the newly create recipes to the image to be deployed you have to edit conf/local.conf file by adding the following lines: 
'IMAGE_INSTALL_append = " hearthmonitor ppgreader"'
'KERNEL_MODULE_AUTOLOAD += "ppgreader"'.

You can now build the new image by issuing the command: 
'bitbake core-image-minimal'
