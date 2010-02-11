// $Id$

Drupal.behaviors.openlayers_geocoder = function (context) {

  if (Drupal.jsAC) {
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
  
  }
  
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
    data: 'query=' + query + '&fieldname=' + fieldname,
    dataType: 'json',
    success: function(point){
	  if (point.longitude && point.latitude) {
	      
      var mapElement = $('#openlayers-cck-widget-map-' + fieldname);
      var data = $(mapElement).data('openlayers');
      var googleProjection = new OpenLayers.Projection('EPSG:900913');
      var geometry = new OpenLayers.Geometry.Point(point.longitude, point.latitude).transform(data.map.options.projection, googleProjection);
      var bounds = new OpenLayers.Bounds(point.box.west, point.box.south, point.box.east, point.box.north).transform(data.map.options.projection, googleProjection);
      data.openlayers.zoomToExtent(bounds);
      
      var vectorLayers = data.openlayers.getLayersBy('CLASS_NAME', "OpenLayers.Layer.Vector");
      vectorLayers[0].addFeatures([new OpenLayers.Feature.Vector(geometry)]);
	      
      // Adding CCK fields autocompletion
      if (point.fields) {
    	jQuery.each(point.fields, function () {
    		$("input[name*='" + this.name + "']").val(this.value);
    		if (!this.override) {
        	  $("input[name*='" + this.name + "']").attr('readonly', 'TRUE').addClass('readonly');
    		}
    	});
      }	  
	  }
   }
 });

}







