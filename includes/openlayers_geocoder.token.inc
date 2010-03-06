<?php
// $Id$

/**
 * @file
 * Token module integration.
 *
 * @ingroup token
 */

/**
 * Implementation of hook_token_list()
 */
function openlayers_geocoder_token_list($type = 'all') {
  if ($type == 'geocoder') {

    $tokens = array();
    $tokens['geocoder']['address'] = t('Full address');
    $tokens['geocoder']['thoroughfare'] = t('Thoroughfare (<em>i.e. street name + number</em>)');
    $tokens['geocoder']['postal_code'] = t('Postal code');
    $tokens['geocoder']['locality'] = t('Locality (<em>i.e. city or town name</em>)');
    $tokens['geocoder']['dependent_locality'] = t('Dependent locality');
    $tokens['geocoder']['sub_administrative_area'] = t('Sub-administrative area');
    $tokens['geocoder']['administrative_area'] = t('Administrative area');
    $tokens['geocoder']['country'] = t('Country name');
    $tokens['geocoder']['country_code'] = t('Country code (<em>in <a href="!url" target="_blank">ISO 3166-1</a> format</em>).', array('!url' => 'http://www.iso.org/iso/english_country_names_and_code_elements'));
    $tokens['geocoder']['accuracy'] = t('Accurancy level (<em>see <a href="!url" target="_blank">Geocoding Accuracy</a></em>)', array('!url' => 'http://code.google.com/apis/maps/documentation/geocoding/index.html#GeocodingAccuracy'));

    return $tokens;
  }
}

/**
 * Implementation of hook_token_values()
 */
function openlayers_geocoder_token_values($type, $object = NULL, $options = array()) {
  if ($type == 'geocoder') {

    $location = openlayers_geocoder_parse_response($object->Placemark[0]);

    $tokens = array();
    $tokens['address'] = $location['address'];
    $tokens['accuracy'] = $location['Accuracy'];
    $tokens['administrative_area'] = $location['AdministrativeAreaName'];
    $tokens['dependent_locality'] = $location['DependentLocalityName'];
    $tokens['postal_code'] = $location['PostalCodeNumber'];
    $tokens['thoroughfare'] = $location['ThoroughfareName'];
    $tokens['locality'] = $location['LocalityName'];
    $tokens['country'] = $location['CountryName'];
    $tokens['country_code'] = $location['CountryNameCode'];
    $tokens['sub_administrative_area'] = $location['SubAdministrativeAreaName'];

    return $tokens;
  }
}

/**
 * Parse geocoder response looking for well known attributes.
 *
 * @param $response
 *    Geocoder response object
 * @param $result
 *    List of well known attributes
 */
function openlayers_geocoder_parse_response(&$response, &$result = array()) {
  $attributes = array('address', 'Accuracy', 'AdministrativeAreaName', 'DependentLocalityName', 'PostalCodeNumber', 'ThoroughfareName', 'LocalityName', 'CountryName', 'CountryNameCode', 'SubAdministrativeAreaName');
  foreach ($response as $key => $value) {
    if ((is_string($value) || is_int($value)) && in_array($key, $attributes)) {
      $result[$key] = $value;
    }
    elseif (is_object($value) || is_array($value)) {
      openlayers_geocoder_parse_response($value, $result);
    }
  }
  return $result;
}
