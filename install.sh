#!/bin/bash

# Only used for development and testing purposes!
if pushd "htdocs/sites/default" > /dev/null; then
  drush sql-drop -y
  drush site-install dh_core --site-name="Drupalhagen" -y --account-name=admin --account-pass=1234
  drush vset cron_key "cron-drupalhagen2014"
fi
