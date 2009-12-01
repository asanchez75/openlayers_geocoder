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
    $tokens['geocoder']['address'] = t("Full address");
    $tokens['geocoder']['locality'] = t("Locality");
    $tokens['geocoder']['country'] = t("Country");
    $tokens['geocoder']['country_code'] = t("Country code");
//    $tokens['geocoder']['street'] = t("Street");
//    $tokens['geocoder']['postalcode'] = t("Postalcode");
//    $tokens['geocoder']['administrative_area'] = t("Administrative area");

    return $tokens;
  }
}

/**
 * Implementation of hook_token_values()
 */
function openlayers_geocoder_token_values($type, $object = NULL, $options = array()) {
  if ($type == 'geocoder') {
    $tokens['address'] = $object->Placemark[0]->address;
    $tokens['locality'] = $object->Placemark[0]->AddressDetails->Country->AdministrativeArea->SubAdministrativeArea->Locality->LocalityName;
    $tokens['country'] = $object->Placemark[0]->AddressDetails->Country->CountryName;
    $tokens['country_code'] = $object->Placemark[0]->AddressDetails->Country->CountryNameCode;

    return $tokens;
  }
}

