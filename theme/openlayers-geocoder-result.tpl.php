<?php
/**
 * @file: openlayers-geocoder-result.tpl.php
 *
 * Template file theming geocoder's response results.
 */
?>
<span class="openlayers-geocoder-result detail-row-1"><?php print $street_address; ?></span>
<span class="openlayers-geocoder-result detail-row-2"><?php print $postal_code .' '. $locality; ?><?php print $locality ? ' - ' : ''; ?><?php print $country; ?></span>
