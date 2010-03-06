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
      // Add-on for OpenLayer Geocoder module
      if ($(this.input).attr('geoautocomplete')) {
        geocoder = new Drupal.Geocoder(this);
        geocoder.process(this.input.value);
      }
    }
    this.selected = false;
    
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

        var data = $('#openlayers-cck-widget-map-' + fieldname).data('openlayers');
        var displayProjection = new OpenLayers.Projection('EPSG:' + data.map.displayProjection);
        var projection = new OpenLayers.Projection('EPSG:' + data.map.projection);
        var vectorLayers = data.openlayers.getLayersBy('CLASS_NAME', "OpenLayers.Layer.Vector");
        var geometry = new OpenLayers.Geometry.Point(point.longitude, point.latitude).transform(displayProjection, projection);
        var bounds = new OpenLayers.Bounds(point.box.west, point.box.south, point.box.east, point.box.north).transform(displayProjection, projection);

        // Add point. For each new search all previous features will be removed.
        data.openlayers.zoomToExtent(bounds);
        vectorLayers[0].removeFeatures(vectorLayers[0].features);
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







