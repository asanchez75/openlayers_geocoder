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
  var formid = $("input[name=form_id]").val();
  var contenttype = formid.replace("_node_form", "");

// console.log(fieldname);
// console.log(dashed);
// console.log(formid);
// console.log(contenttype);
  var data = {
    query:query,
    fieldname:fieldname,
    content_type:contenttype
  };
//console.log(data);
console.log(this);
  $.ajax({
    type: 'POST',
    url: this.data.db.uri + '/process',
    data: data,
    dataType: 'json',
    success: function(point) {

      if (point.longitude && point.latitude) {

        var data = $('#openlayers-cck-widget-map-' + fieldname).data('openlayers');
        if (!data.map.displayProjection) {
          data.map.displayProjection = 4326;
        }
        var displayProjection = new OpenLayers.Projection('EPSG:' + data.map.displayProjection);
        var projection = new OpenLayers.Projection('EPSG:' + data.map.projection);
        var vectorLayer = data.openlayers.getLayersBy('drupalID', "openlayers_drawfeatures_layer");
        var geometry = new OpenLayers.Geometry.Point(point.longitude, point.latitude).transform(displayProjection, projection);
        var bounds = new OpenLayers.Bounds(point.box.west, point.box.south, point.box.east, point.box.north).transform(displayProjection, projection);

        //Remove all points, unless CCK widget settings prevent it.
        if (point.keep_points) {
          data.openlayers.setCenter(new OpenLayers.LonLat(point.longitude, point.latitude).transform(displayProjection, projection));
        }
        else {
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
        }

        //Add point to map.
        vectorLayer[0].addFeatures([new OpenLayers.Feature.Vector(geometry)]);
      }
    }
  });

}

Drupal.behaviors.openlayerFieldWktHide.attach = function(context, settings) {
  // Hide WKT field and allow to toggle visibility.
  if (typeof Drupal.settings.openlayers_cck.wkt_hide != 'undefined') {
    var textShow = Drupal.settings.openlayers_cck.wkt_hide.text_show;
    var textHide = Drupal.settings.openlayers_cck.wkt_hide.text_hide;

    for (field in Drupal.settings.openlayers_cck.wkt_hide.fields) {
      var fieldID = '#edit-' + field + '-openlayers-wkt-wrapper';

      $(fieldID + ':not(.openlayers-cck-processed)').each(function() {
        var $thisField = $(this);

        $thisField.addClass('openlayers-cck-processed');
        // Add a link to be able to hide and show, and hide by default.
        var link = $('<a href="" id="' + field + '-toggle" class="openlayers-cck-hide-link">' + textShow + '</a>')
          .data('fieldID', fieldID);
        $thisField.before(link)
          .hide();
        $('#' + field + '-toggle').toggle(
          function () {
            var $thisLink = $(this);
            var localFieldID = $thisLink.data('fieldID');
            $(localFieldID).slideDown();
            $thisLink.text(textHide);
          },
          function () {
            var $thisLink = $(this);
            var localFieldID = $thisLink.data('fieldID');
            $(localFieldID).slideUp();
            $thisLink.text(textShow);
          }
        );
      });
    }
  }
};

})(jQuery);





