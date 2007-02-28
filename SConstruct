# -*- encoding:utf8 -*-

import ConfigParser, glob

config = ConfigParser.ConfigParser()
config.read('build.cfg')

builds = {}
for i in config.sections():
    l = i.split(".")
    id = l[0]
    if len(l) >= 2 and l[1] != str(Platform()):
        continue
    builds[id] = { "libs" : config.get(i, "libs").split(",")
                 , "flags" : config.get(i, "flags")
                 , "sources" : glob.glob(config.get(i, "sources"))
                 }

print builds["vicinibus"]

for i, j in builds.iteritems():
    env = Environment (CXXFLAGS = j["flags"])
    env.Program (i, j["sources"], LIBS=j["libs"])
    print "Building " + i + "..."
