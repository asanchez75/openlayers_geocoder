<?php
/**
 * @file: openlayers-geocoder-result.tpl.php
 *
 * Template file theming geocoder's response results.
 */
?>
<span class="openlayers-geocoder-result detail-row-1"><?php print $result['ThoroughfareName'] ? $result['ThoroughfareName'] : $result['address']; ?></span>
<span class="openlayers-geocoder-result detail-row-2"><?php print $result['LocalityName']; ?><?php print $result['LocalityName'] ? ' - ' : ''; ?><?php print $result['CountryName']; ?></span>