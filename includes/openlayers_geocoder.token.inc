<?php

/**
 * @file
 * Token module integration.
 *
 * @ingroup token
 */

/**
 * Implementation of hook_token_info().
 */
function openlayers_geocoder_token_info() {
  // @todo support for views api
  $type = array(
     'name' => t('Geocoder'),
     'description' => t('Tokens related to geocoder.'),
     'needs-data' => 'node',
   );

  $geocoder['formatted_address'] = array(
    'name' => t('Full formatted address.'),
    'description' => t('Full formatted address.'),
    );
  $geocoder['street_address'] = array(
    'name' => t('Indicates a precise street address.'),
    'description' => t('Indicates a precise street address.'),
    );

  $geocoder['route'] = array(
    'name' => t('Indicates a named route (such as "US 101").'),
    'description' => t('Indicates a named route (such as "US 101").'),
    );

  $geocoder['intersection'] = array(
    'name' => t('Indicates a major intersection, usually of two major roads.'),
    'description' => t('Indicates a major intersection, usually of two major roads.'),
    );

  $geocoder['political'] = array(
    'name' => t('Indicates a political entity. Usually, this type indicates a polygon of some civil administration.'),
    'description' => t('Indicates a political entity. Usually, this type indicates a polygon of some civil administration.'),
    );

  $geocoder['country'] = array(
    'name' => t('Indicates the national political entity, and is typically the highest order type returned by the Geocoder.'),
    'description' => t('Indicates the national political entity, and is typically the highest order type returned by the Geocoder.'),
    );

  $geocoder['country_code'] = array(
    'name' => t('Country code (<em>in <a href="!url" target="_blank">ISO 3166-1</a> format</em>).', array('!url' => 'http://www.iso.org/iso/english_country_names_and_code_elements')),
    'description' => t('Country code (<em>in <a href="!url" target="_blank">ISO 3166-1</a> format</em>).', array('!url' => 'http://www.iso.org/iso/english_country_names_and_code_elements')),
    );

  $geocoder['administrative_area_level_1'] = array(
    'name' => t('Indicates a first-order civil entity below the country level. Within the United States, these administrative levels are states. Not all nations exhibit these administrative levels.'),
    'description' => t('Indicates a first-order civil entity below the country level. Within the United States, these administrative levels are states. Not all nations exhibit these administrative levels.'),
    );

  $geocoder['administrative_area_level_2'] = array(
    'name' => t('Indicates a second-order civil entity below the country level. Within the United States, these administrative levels are counties. Not all nations exhibit these administrative levels.'),
    'description' => t('Indicates a second-order civil entity below the country level. Within the United States, these administrative levels are counties. Not all nations exhibit these administrative levels.'),
    );

  $geocoder['administrative_area_level_3'] = array(
    'name' => t('Indicates a third-order civil entity below the country level. This type indicates a minor civil division. Not all nations exhibit these administrative levels.'),
    'description' => t('Indicates a third-order civil entity below the country level. This type indicates a minor civil division. Not all nations exhibit these administrative levels.'),
    );


  $geocoder['colloquial_area'] = array(
    'name' => t('Indicates a commonly-used alternative name for the entity.'),
    'description' => t('Indicates a commonly-used alternative name for the entity.'),
    );

  $geocoder['locality'] = array(
    'name' => t('Indicates an incorporated city or town political entity.'),
    'description' => t('Indicates an incorporated city or town political entity.'),
    );

  $geocoder['sublocality'] = array(
    'name' => t('Indicates an first-order civil entity below a locality'),
    'description' => t('Indicates an first-order civil entity below a locality'),
    );

  $geocoder['neighborhood'] = array(
    'name' => t('Indicates a named neighborhood'),
    'description' => t('Indicates a named neighborhood'),
    );

  $geocoder['premise'] = array(
    'name' => t('Indicates a named location, usually a building or collection of buildings with a common name'),
    'description' => t('Indicates a named location, usually a building or collection of buildings with a common name'),
    );

  $geocoder['subpremise'] = array(
    'name' => t('Indicates a first-order entity below a named location, usually a singular building within a collection of buildings with a common name'),
    'description' => t('Indicates a first-order entity below a named location, usually a singular building within a collection of buildings with a common name'),
    );

  $geocoder['postal_code'] = array(
    'name' => t('Indicates a postal code as used to address postal mail within the country.'),
    'description' => t('Indicates a postal code as used to address postal mail within the country.'),
    );

  $geocoder['natural_feature'] = array(
    'name' => t('Indicates a prominent natural feature.'),
    'description' => t('Indicates a prominent natural feature.'),
    );

  $geocoder['airport'] = array(
    'name' => t('Indicates an airport.'),
    'description' => t('Indicates an airport.'),
    );

  $geocoder['park']  = array(
    'name' => t('Indicates a named park.'),
    'description' => t('Indicates an airport.'),
    );

  $geocoder['point_of_interest']  = array(
    'name' => t('Indicates a named point of interest. Typically, these "POI"s are prominent local entities that don\'t easily fit in another category such as "Empire State Building" or "Statue of Liberty."'),
    'description' => t('Indicates a named point of interest. Typically, these "POI"s are prominent local entities that don\'t easily fit in another category such as "Empire State Building" or "Statue of Liberty."'),
    );

   $geocoder['post_box']  = array(
    'name' => t('Indicates a specific postal box.'),
    'description' => t('Indicates a specific postal box.'),
    );


   $geocoder['street_number']  = array(
    'name' => t('Indicates the precise street number.'),
    'description' => t('Indicates the precise street number.'),
    );

   $geocoder['floor']  = array(
    'name' => t('Indicates the floor of a building address.'),
    'description' => t('Indicates the floor of a building address.'),
    );

   $geocoder['room']  = array(
    'name' => t('Indicates the room of a building address.'),
    'description' => t('Indicates the room of a building address.'),
    );

   $geocoder['latitude'] = array(
    'name' => t('Latitude'),
    'description' => t('Latitude'),
    );

   $geocoder['longitude'] = array(
    'name' => t('Longitude'),
    'description' => t('Longitude'),
    );
   // Keep v2 tokens for backward compatibility
   $geocoder['address'] = array(
    'name' => t(' <b>Deprecated: use "street_address" instead.</b> Full address'),
    'description' => t(' <b>Deprecated: use "street_address" instead.</b> Full address'),
    );

   $geocoder['thoroughfare'] = array(
    'name' => t(' <b>Deprecated: use "route" or "street_address" instead.</b> Thoroughfare (<em>i.e. street name + number</em>)'),
    'description' => t(' <b>Deprecated: use "route" or "street_address" instead.</b> Thoroughfare (<em>i.e. street name + number</em>)'),
    );

   $geocoder['administrative_area'] = array(
    'name' => t(' <b>Deprecated: use "administrative_area_level_1" instead.</b> Administrative area'),
    'description' => t(' <b>Deprecated: use "administrative_area_level_1" instead.</b> Administrative area'),
    );


   $geocoder['sub_administrative_area'] = array(
    'name' => t(' <b>Deprecated: use "administrative_area_level_2" instead.</b> Sub-administrative area'),
    'description' => t(' <b>Deprecated: use "administrative_area_level_2" instead.</b> Sub-administrative area'),
    );

   $geocoder['dependent_locality'] = array(
    'name' => t(' <b>Deprecated: use "administrative_area_level_3" instead.</b> Dependent locality'),
    'description' => t(' <b>Deprecated: use "administrative_area_level_3" instead.</b> Dependent locality'),
    );


   return array(
     'types' => array('geocoder' => $type),
     'tokens' => array('geocoder' => $geocoder),
   );
}

/**
 * Implementation of hook_tokens().
 */
function openlayers_geocoder_tokens($type, $tokens, array $data = array(), array $options = array()) {
  // @todo support for openlayers_data
  if ($type == 'geocoder' && !empty($data['openlayers_geocoder'])) {
    $object = $data['openlayers_geocoder'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'locality':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'administrative_area_level_2':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'administrative_area_level_1':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'country':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'country_code':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'street_address':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        case 'latitude':
          $replacements[$original] = isset($object['location']['lat']) ? $object['location']['lat'] : '';
        break;
        case 'longitude':
          $replacements[$original] = isset($object['location']['lat']) ? $object['location']['lat'] : '';
        break;
        case 'formatted_address':
          $replacements[$original] = isset($object['address']) ? $object['address'] : '';
        break;
        case 'street_address':
          $replacements[$original] = isset($object['components'][$name]) ? $object['components'][$name] : '';
        break;
        // Keep v2 tokens for backward compatibility
        case 'address':
          $replacements[$original] = $object['components']['street_address'] ? $replacements['street_address'] : '';
        break;
        case 'thoroughfare':
          $replacements[$original] = $object['components']['route'] ? $tokens['route'] . ' '. $replacements['street_number'] : '';
        break;
        case 'administrative_area':
          $replacements[$original] = $object['components']['administrative_area_level_1'] ? $replacements['administrative_area_level_1'] : '';
        break;
        case 'sub_administrative_area':
          $replacements[$original] = $object['components']['administrative_area_level_2'] ? $replacements['administrative_area_level_2'] : '';
        break;
        case 'dependent_locality':
          $replacements[$original] = $object['components']['administrative_area_level_3'] ? $replacements['administrative_area_level_3'] : '';
        break;

    }

  }

  }
  return $replacements;
}
/**
 * Progammatically geocode a node.
 *
 * @param $node
 *    Node object
 * @param $field_name
 *    OpenLayers CCK field using OpenLayers Geocoder widget
 * @param $q
 *    Location query
 * @param $save_node
 *    Save or just modify node object
 */
function openlayers_geocoder_geocode_node(&$node, $field_name, $q, $save_node = FALSE) {

  $field = content_fields($field_name, $node->type);
  if (isset($node->{$field_name}) && $response = openlayers_geocoder_response($q)) {
    $location = $response[0]['location'];
    $node->{$field_name}[0]['openlayers_wkt'] = 'GEOMETRYCOLLECTION(POINT('. $location['lng'] .' '. $location['lat'] .'))';

    $settings = openlayers_geocoder_widget_parse_settings($field['widget']);
    foreach ($settings as $name => $setting) {
      if ($setting['enable']) {
        $content = token_replace($setting['content'], 'geocoder', $response[0]);
        $node->{$name}[0]['value'] = $content;
      }
    }

    if ($save_node) {
      node_save($node);
    }
    return TRUE;
  }
  return FALSE;
}
