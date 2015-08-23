(function ($, Drupal) {

  var original_function = Drupal.ikto_photoswipe.get_gallery_images;

  Drupal.ikto_photoswipe.get_gallery_images = function ($gallery_element) {
    var $images = original_function($gallery_element);

    $images = $images.filter(function () {
      return !$(this).parents('.slick-cloned').length;
    });

    return $images;
  };

})(jQuery, Drupal);
