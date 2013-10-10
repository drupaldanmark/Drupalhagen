; API
api = 2

; Core
core = 7.x

; Drupal project
projects[drupal] = 7.23

; We are going to run with panopoly beneath it all so lets fetch it!
projects[panopoly][type] = profile
projects[panopoly][download][type] = git
projects[panopoly][download][url] = http://git.drupal.org/project/panopoly.git
projects[panopoly][download][revision] = 158a9ca29352fd943f542a8d3dbfd4bc220fc706
projects[panopoly][download][branch] = 7.x-1.x

projects[mothership][type] = theme
projects[mothership][version] = 2.10

projects[hagen2013][type] = theme
projects[hagen2013][download][type] = git
projects[hagen2013][download][url] = git@github.com:drupaldanmark/hagen2013.git
projects[hagen2013][download][branch] = master

projects[campkitlite_core][type] = module
projects[campkitlite_core][download][type] = git
projects[campkitlite_core][download][url] = git@github.com:drupaldanmark/campkitlite.git
projects[campkitlite_core][download][branch] = master

projects[simple_gmap][type] = module
projects[simple_gmap][download][type] = git
projects[simple_gmap][download][url] = http://git.drupal.org/project/simple_gmap.git
projects[simple_gmap][download][revision] = e840cf742393fa6ef4fa
projects[simple_gmap][download][branch] = 7.x-1.x
