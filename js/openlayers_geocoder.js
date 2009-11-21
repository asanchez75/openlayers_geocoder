// $Id$

Drupal.behaviors.openlayers_geocoder = function (context) {

  /**
   * Hides the autocomplete suggestions
   */
  Drupal.jsAC.prototype.hidePopup = function (keycode) {
    // Select item if the right key or mousebutton was pressed
    if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
      this.input.value = this.selected.autocompleteValue;
    }
    // Hide popup
    var popup = this.popup;
    if (popup) {
      this.popup = null;
      $(popup).fadeOut('fast', function() { $(popup).remove(); });
    }
    this.selected = false;
    
    // Add-on for OpenLayer Geocoder module
    if ($(this.input).attr('geoautocomplete')) {
      geocoder = new Drupal.Geocoder(this);
      geocoder.process(this.input.value);
    }
  };
  
};


/**
 * Geocoder object
 */
Drupal.Geocoder = function (data) {
  this.data = data;
};

/**
 * Performs a search
 */
Drupal.Geocoder.prototype.process = function (query) {
  
  var fieldname = $(this.data.input).attr('fieldname');
  var dashed = $(this.data.input).attr('dashed');

  $.ajax({
    type: 'POST',
    url: this.data.db.uri + '/coordinates',
    data: 'query=' + query,
    dataType: 'json',
    success: function(point){

      var MapId = 'openlayers-cck-widget-map-' + fieldname;
      var projection = new OpenLayers.Projection(OL.maps[MapId].map.baseLayer.projection.getCode());
      var displayProjection = new OpenLayers.Projection(OL.maps[MapId].map.displayProjection.getCode());
      var bounds = new OpenLayers.Bounds(point.box.west, point.box.south, point.box.east, point.box.north).transform(displayProjection, projection);
      var InputId = 'input#edit-' + dashed + '-openlayers-wkt-hidden';
      
      $(InputId).attr('value', 'POINT(' + point.longitude + ' ' + point.latitude + ')');
      OL.CCK.populateMap(MapId);
      OL.maps[MapId].map.zoomToExtent(bounds);
   }
 });

}







