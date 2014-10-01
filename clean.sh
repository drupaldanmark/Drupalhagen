#!/bin/bash
if [ -d "cleaned" ]; then
  rm -rf cleaned
fi

git clone ssh://codeserver.dev.a43ba044-0e08-cdc0-6e00-9bb3b3bfb41e@codeserver.dev.a43ba044-0e08-cdc0-6e00-9bb3b3bfb41e.drush.in:2222/~/repository.git cleaned

if pushd cleaned > /dev/null; then
  cp -prv ../htdocs/profiles/dh_core profiles

  if pushd profiles/dh_core > /dev/null; then
  	find . -name ".git" | xargs rm -rf
  	find . -name ".gitignore" | xargs rm
  	popd > /dev/null;
  fi

  git add .
  TAG=`date +%Y-%m-%dT%H%M`
  git commit -m "Build ${TAG}"
  git push origin master

  popd > /dev/null;
fi
