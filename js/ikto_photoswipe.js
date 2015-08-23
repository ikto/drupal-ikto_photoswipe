(function ($, Drupal, PhotoSwipe, PhotoSwipeUI_Default) {

  Drupal.ikto_photoswipe = Drupal.ikto_photoswipe || {};

  var ikto_photoswipe = Drupal.ikto_photoswipe;

  ikto_photoswipe.gallery_uid_seed = 0;

  /**
   * Gets pswp element (gallery template) from document
   */
  ikto_photoswipe.get_pswp_element = function () {
    var $pswp = $('.pswp');
    if (!$pswp.length) {
      $(Drupal.settings.ikto_photoswipe.pswp_element).appendTo('body');
      $pswp = $('.pswp');
    }

    return $pswp[0];
  };

  /**
   * Gets image element (jQuery collection) from gallery element (jQuery collection)
   */
  ikto_photoswipe.get_gallery_images = function ($gallery_element) {
    return $gallery_element.find('.ikto-photoswipe');
  };

  /**
   * Opens gallery by it's DOM element and slide index
   */
  ikto_photoswipe.open_gallery = function (gallery_element, slide_index, options) {
    var $gallery_element = $(gallery_element);

    var pswp_element = ikto_photoswipe.get_pswp_element();
    if (typeof pswp_element == 'undefined') {
      console.log('Unable to get pswp element, using PhotoSwipe is impossible');
      return;
    }
    var items = [];
    options = options || Drupal.settings.ikto_photoswipe.defaults;

    var $images = ikto_photoswipe.get_gallery_images($gallery_element);
    $images.each(function () {
      var $image = $(this);
      items.push({
        src: $image.attr('href'),
        w: $image.data('width'),
        h: $image.data('height'),
        title: $image.data('title')
      });
    });

    options.index = slide_index;
    options.galleryUID = $gallery_element.data('gallery-uid');

    var gallery = new PhotoSwipe(pswp_element, PhotoSwipeUI_Default, items, options);
    gallery.init();
  };

  /**
   * Handles click on gallery image (to open gallery)
   */
  ikto_photoswipe.image_click_handler = function (event) {
    event = event || window.event;
    event.preventDefault ? event.preventDefault() : event.returnedValue = false;

    var $clicked_item = $(event.target || event.srcElement).closest('.ikto-photoswipe');
    if (!$clicked_item.length) {
      return;
    }

    var $clicked_gallery = $clicked_item.closest('.ikto-photoswipe-gallery');

    var index = ikto_photoswipe.get_gallery_images($clicked_gallery).index($clicked_item);
    if (index >= 0) {
      ikto_photoswipe.open_gallery($clicked_gallery, index);
    }

    return false;
  };

  /**
   * Parse url hash to get desired gallery and image ids
   * Code taken from http://photoswipe.com/documentation/getting-started.html
   */
  ikto_photoswipe.parse_hash = function () {
    var hash = window.location.hash.substring(1),
      params = {};

    if(hash.length < 5) {
      return params;
    }

    var vars = hash.split('&');
    for (var i = 0; i < vars.length; i++) {
      if(!vars[i]) {
        continue;
      }
      var pair = vars[i].split('=');
      if(pair.length < 2) {
        continue;
      }
      params[pair[0]] = pair[1];
    }

    if(params.gid) {
      params.gid = parseInt(params.gid, 10);
    }

    return params;
  };

  Drupal.behaviors.ikto_photoswipe = {
    attach: function (context, settings) {

      /**
       * Step 1: Look for all single photoswipe images and make galleries with them
       */
      var $single_images = $('a.ikto-photoswipe', context).filter(function(element) {
        return !$(this).parents('.ikto-photoswipe-gallery').length;
      });
      $single_images.once('ikto-photoswipe-single-image', function () {
        var $image_link = $(this);
        $image_link.wrap('<span class="ikto-photoswipe-gallery"></span>');
      });

      /**
       * Step 2: Look for photoswipe galleries, bind click handler which opens gallery
       */
      var $galleries = $('.ikto-photoswipe-gallery', context);
      $galleries.once('ikto-photoswipe-galley', function () {
        var $gallery = $(this);
        $gallery.attr('data-gallery-uid', (++ikto_photoswipe.gallery_uid_seed).toString());
        $gallery.on('click', ikto_photoswipe.image_click_handler);
      });

      /**
       * Step 3: Open gallery if we have one specified by url hash
       */
      $('body', context).once('ikto-photoswipe-initial-gallery', function () {
        var hash_data = ikto_photoswipe.parse_hash();
        if ((hash_data.gid > 0) && (hash_data.pid > 0)) {
          // Cancel opening process if specified gallery does not exist
          if (typeof $galleries[hash_data.gid - 1] == 'undefined') {
            return;
          }

          ikto_photoswipe.open_gallery($galleries[hash_data.gid - 1], hash_data.pid - 1);
        }
      });
    }
  };
})(jQuery, Drupal, PhotoSwipe, PhotoSwipeUI_Default);
