<?php

/**
 * @file
 * Theme function for OpenLayers Geocoder widget autocompletion setting
 */
function theme_openlayers_geocoder_autocompletion_settings($element) {
  $rows = array();
  $childs = element_children($element['element']);

  foreach ($childs as $key => $value) {
    if (is_numeric($value)) {
      $row = array();
      $subchilds = element_children($element['element'][$key]);
      foreach ($subchilds as $field) {
        $row[] = drupal_render($element['element'][$key][$field]);
      }
      $rows[] = $row;
    }
    else {
      $token_help =drupal_render($element['element'][$value]);
    }
  }
  $header[] = t('Enable');
  $header[] = t('Override');
  $header[] = t('Field');
  $header[] = t('Content');
  return theme('table', array('header' => $header, 'rows' => $rows)) . $token_help;
}
