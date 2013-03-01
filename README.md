pivot
=====

Simple program which switches through two alternating screen orientations/roations.

Usage:
-----
    usage: pivot [options] [ rotation_1 [ rotation_2 ]]
      -h, --help     prints help
      -d, --display  display
      -f, --force    force switching
    
    rotations: left, right, normal, inverted
    default rotations: left, normal

### examples

Switches between *right* and *normal* orientation, no matter what the actual orientation is:

    $ pivot -f right

Switches between *left* and *inverted* (upside down), unless the actual orientation is none of them:

	$ pivot left inverted

Details
-------

See [Xrandr (3)](http://linux.die.net/man/3/xrandr)
