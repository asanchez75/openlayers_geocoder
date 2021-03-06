(function($){

Drupal.behaviors.openlayersGeocoder = {};
Drupal.behaviors.openlayersGeocoder.attach = function(context, settings) {
  if (Drupal.jsAC) {
     /**
    * Hides the autocomplete suggestions
    */
  Drupal.jsAC.prototype.hidePopup = function (keycode) {
  // Select item if the right key or mousebutton was pressed.
  if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
    this.input.value = $(this.selected).data('autocompleteValue');
  }
  // Hide popup.
  var popup = this.popup;
  if (popup) {
    this.popup = null;
    $(popup).fadeOut('fast', function () { $(popup).remove(); });
    // Add-on for OpenLayer Geocoder module
    if ($(this.input).attr('geoautocomplete')) {
      geocoder = new Drupal.Geocoder(this);
      geocoder.process(this.input.value);
    }
  }
  this.selected = false;
  $(this.ariaLive).empty();
};


  }
}

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
  var bundle_name = $(this.data.input).attr('bundle_name');
  var entity_type = $(this.data.input).attr('entity_type');

  var data = {
    query:query,
    fieldname:fieldname,
    entity_type:entity_type,
    bundle_name:bundle_name
  };

  $.ajax({
    type: 'POST',
    url: this.data.db.uri + '/process',
    data: data,
    dataType: 'json',
    success: function(point) {

      if (point.longitude && point.latitude) {
        var data = $('#edit-' + dashed + ' #openlayers-map').data('openlayers');

        if (!data.map.displayProjection) {
          data.map.displayProjection = 4326;
        }
        var displayProjection = new OpenLayers.Projection(data.map.displayProjection); // 4326
        var projection = new OpenLayers.Projection(data.map.projection); // 3857
        var vectorLayer = data.openlayers.getLayersBy('drupalID', "openlayers_behavior_geofield");
        var geometry = new OpenLayers.Geometry.Point(point.longitude, point.latitude).transform(displayProjection, projection);
        var bounds = new OpenLayers.Bounds(point.box.west, point.box.south, point.box.east, point.box.north).transform(displayProjection, projection);
          vectorLayer[0].removeFeatures(vectorLayer[0].features);
          data.openlayers.zoomToExtent(bounds);
          // Adding CCK fields autocompletion
          if (point.fields) {
            jQuery.each(point.fields, function () {
              $(this.type + "[name*='" + this.name + "']").attr('value', this.value);
              if (!this.override) {
                $(this.type + "[name*='" + this.name + "']").attr('readonly', 'TRUE').addClass('readonly');
              }
            });
          }

        //Add point to map.
        vectorLayer[0].addFeatures([new OpenLayers.Feature.Vector(geometry)]);
      }
    }
  });

}

})(jQuery);





