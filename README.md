# DTTagAndProbe

**DISCLAIMER: package still under development, not for general use for now.**

Repository with CMS DT tag-and-probe based analyses. Presently including base classes and a prototype macro to run segment efficiency computation.

## How to run the segment tag-and-probe analysis
```
# edit your config file e.g.
# emacs -nw config/config.ini

root -b
root [0] .L loadTnP.C
root [1] loadSegmentTnP()
root [2] DTTnPSegmentEff TnP("config/config.ini")
root [3] TnP.Loop()
root [4] .q

# results will be stored in a given rootfile configurable from .ini

# edit your plotter config file e.g.
# emacs -nw config/configPlotter.json

# to plot results run:
python plotter.py config/configPlotter.json
```
