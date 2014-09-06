<?php
/**
 * @file
 * Implements some developer commands.
 */


/**
 * Implements hook_drush_command().
 */
function build_drush_command() {
  $items = array();

  $items['build'] = array(
    'description' => 'Runs database updates, reverts features and clears caches.',
    'callback' => '_drush_build',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['devify'] = array(
    'description' => 'Configures the current database for development.',
    'callback' => '_drush_devify',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'options' => array(
      'enable-modules' => 'A comma separated list of modules to enable.',
      'disable-modules' => 'A comma separated list of modules to disable.',
      'delete-variables' => 'A comma separated list of variables to delete.',
      'reset-variables' => 'A comma separated list of variables to reset with ' .
        'the format foo=var,hey=ho.',
    ),
    'examples' => array(
      'drush devify' => 'Uses command default values to set up a database for development.',
      'drush devify --enable-modules=xhprof,devel' => 'Enables XHProf and Devel modules',
      'drush devify --reset-variables=site_mail=local@local.com,file_temporary_path=/tmp'
      => 'Resets site_mail and file_temporary_path variables.',
    ),
  );

  return $items;
}

/**
 * Executes the build commands.
 */
function _drush_build() {
  drush_invoke('updatedb');
  // We should not revert features for kvinfo project.
  // Implement hook_update_n calls for that instead.
//    drush_invoke_process(
//      '@self',
//      'features-revert-all',
//      array(),
//      array(
//        'force' => true,
//        'yes' => true,
//      )
//    );
  drush_invoke('cc', array('type' => 'all'));
  drush_log(dt('Built!'), 'success');
}

/**
 * Callback for drush devify.
 */
function _drush_devify() {
  // Disable modules.
  $modules = drush_get_option('disable-modules', array('update'));
  if (is_string($modules)) {
    $modules = explode(',', $modules);
  }
  module_disable($modules);
  if (!empty($modules)) {
    drush_log(dt('Disabled module: @modules', array('@modules' => implode(', ', $modules))), 'ok');
  }

  // Enable modules.
  $modules = drush_get_option('enable-modules', array());
  if (is_string($modules)) {
    $modules = explode(',', $modules);
  }
  module_enable($modules);
  if (!empty($modules)) {
    drush_log(dt('Enabling module: @modules', array('@modules' => implode(', ', $modules))), 'ok');
  }

  // Delete variables.
  $variables = drush_get_option(
    'delete-variables',
    array(
      'googleanalytics_account',
    )
  );
  if (is_string($variables)) {
    $variables = explode(',', $variables);
  }
  foreach ($variables as $variable) {
    variable_del($variable);
  }
  if (!empty($variables)) {
    drush_log(dt('Deleted variables: @variables', array('@variables' => implode(', ', $variables))), 'ok');
  }

  // Reset variables.
  $variables = drush_get_option(
    'reset-variables',
    array(
      'preprocess_css' => 0,
      'preprocess_js' => 0,
      'cache' => 0,
      'page_compression' => 0,
    )
  );
  if (is_string($variables)) {
    // Explode a=b,c=d into an associative array.
    $variables_raw = explode(',', $variables);
    $variables = array();
    foreach ($variables_raw as $value) {
      $variable = explode('=', $value);
      if (count($variable) == 2) {
        $variables[$variable[0]] = $variable[1];
      }
    }
  }
  foreach ($variables as $name => $value) {
    variable_set($name, $value);
    drush_log(dt('Variable set: @name => @value', array('@name' => $name, '@value' => var_export($value, TRUE))), 'ok');
  }

  // Allow languages to be overwritten on local environments.
  $domains = drush_get_option('local-domains-per-language', array());
  foreach ($domains as $langcode => $domain_fields) {
    db_update('languages')
    ->fields($domain_fields)
    ->condition('language', $langcode)
    ->execute();
    drush_log(dt('Updated language for ' . $langcode), 'ok');
  }

  // Sanitize database.
  // @see sql_drush_sql_sync_sanitize() to add your sanitize queries.
  // drush_sql_sanitize();

  drush_log(dt('Devified!'), 'success');
}
