tp-link-it is a command line program that can turn on, turn off, or reboot a TP-Link
Smart Home plug.  Originally, the author (Ian M. Fink) wrote this for a Unix/Unix-like
command line first and, then, successfully ported it to the Particle Photon.

This software release is mainly to demonstrate that the author can write software that
utilizes TCP sockets and can follow instructions for the authentication process, grokked
from a python script, necessary to provide commands to an appropriately configured
TP-Link Smart Home plug.

tp-link-it, for example, can be utilized to turn on an appropriately configured
TP-Link Smart Home plug:
  bash$  tp-link-it SERVER_NAME on
will instruct the appropriately configured TP-Link Smart Home plug, identified by
SERVER_NAME, to turn “on.”  For instance, SERVER_NAME may be a logical name (e.g.,
plug372.plugs.example.com), resolved by DNS or may be an IP address (e.g.,
192.168.22.231).  In another example, to turn on the appropriately configured
TP-Link Smart Home plug:
  bash$  tp-link-it SERVER_NAME off
will instruct the appropriately configured TP-Link Smart Home plug, identified by
SERVER_NAME, to turn “off.”  

Currently, some extra headers files are needed to kludge things together to compile
on MacOS.  The author longs for the day when Apple was hospitable towards those writing
command line software.  Nevertheless, the author of this will fix this when ported to
Linux.  Regardless, if you are controlling a TP-Link Smart Home plug from the command
line, you stand a good chance of making things work, or at least looking at the
appropriate source files and coming up with your own solution.

TO DO/NOTE: rresvport in tcpopen.c is deprecated (at least on MacOS 12.7.x), but
it still works. This will be updated at a later time.

