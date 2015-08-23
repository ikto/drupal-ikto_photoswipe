<?php

function ikto_photoswipe_admin_settings_form($form, &$form_state) {

  $t = 'ikto_photoswipe_t';

  $form['ikto_photoswipe_formatter_defaults'] = array(
    '#type'         => 'fieldset',
    '#title'        => $t('IKTO PhotoSwipe field formatter defaults'),
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );

  $form['ikto_photoswipe_formatter_defaults']['ikto_photoswipe_formatter_defaults_core'] = array(
    '#type'         => 'fieldset',
    '#title'        => $t('Core options'),
    '#collapsible'  => TRUE,
    '#collapsed'    => FALSE,
    '#tree'         => TRUE,
  );

  $form_core = &$form['ikto_photoswipe_formatter_defaults']['ikto_photoswipe_formatter_defaults_core'];
  $form_core_defaults = ikto_photoswipe_get_global_options_core();

  $form_core['showHideOpacity'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Show Hide Opacity'),
    '#description' => $t('If set to false: background opacity and image scale will be animated (image opacity is always 1). If set to true: root PhotoSwipe element opacity and image scale will be animated. To enable just opacity transition (without scale), do not define getThumbBoundsFn option.'),
    '#default_value' => $form_core_defaults['showHideOpacity'],
  );

  $form_core['showAnimationDuration'] = array(
    '#type' => 'textfield',
    '#title' => $t('Initial zoom-in transition duration in milliseconds'),
    '#description' => $t('Set to 0 to disable.'),
    '#default_value' => $form_core_defaults['showAnimationDuration'],
    '#element_validate' => array('ikto_form_element_validate_integer_not_negative'),
  );

  $form_core['hideAnimationDuration'] = array(
    '#type' => 'textfield',
    '#title' => $t('Initial zoom-out transition duration in milliseconds'),
    '#description' => $t('Set to 0 to disable.'),
    '#default_value' => $form_core_defaults['hideAnimationDuration'],
    '#element_validate' => array('ikto_form_element_validate_integer_not_negative'),
  );

  $form_core['bgOpacity'] = array(
    '#type' => 'textfield',
    '#title' => $t('Background opacity'),
    '#description' => $t('Should be a number from 0 to 1, e.g. 0.7. This style is defined via JS, not via CSS, as this value is used for a few gesture-based transitions.'),
    '#default_value' => $form_core_defaults['bgOpacity'],
    '#element_validate' => array('ikto_form_element_validate_number_zero_one'),
  );

  $form_core['spacing'] = array(
    '#type' => 'textfield',
    '#title' => $t('Spacing ratio between slides'),
    '#description' => $t('For example, 0.12 will render as a 12% of sliding viewport width (rounded).'),
    '#default_value' => $form_core_defaults['spacing'],
    '#element_validate' => array('ikto_form_element_validate_number_not_negative'),
  );

  $form_core['allowPanToNext'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Allow swipe navigation to next/prev item when current item is zoomed'),
    '#default_value' => $form_core_defaults['allowPanToNext'],
  );

  $form_core['maxSpreadZoom'] = array(
    '#type' => 'textfield',
    '#title' => $t('Maximum zoom level when performing spread (zoom) gesture'),
    '#description' => $t('2 means that image can be zoomed 2x from original size. Try to avoid huge values here, as too big image may cause memory issues on mobile (especially on iOS).'),
    '#default_value' => $form_core_defaults['maxSpreadZoom'],
    '#element_validate' => array('ikto_form_element_validate_number_not_negative'),
  );

  $form_core['loop'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Loop slides when using swipe gesture'),
    '#description' => $t("If set to true you'll be able to swipe from last to first image. Option is always false when there are less than 3 slides. This option has no relation to arrows navigation. Arrows loop is turned on permanently. You can modify this behavior by making custom UI."),
    '#default_value' => $form_core_defaults['loop'],
  );

  $form_core['pinchToClose'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Pinch to close gallery gesture'),
    '#description' => $t('The gallery’s background will gradually fade out as the user zooms out. When the gesture is complete, the gallery will close.'),
    '#default_value' => $form_core_defaults['pinchToClose'],
  );

  $form_core['closeOnScroll'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Close gallery on page scroll'),
    '#description' => $t('Option works just for devices without hardware touch support.'),
    '#default_value' => $form_core_defaults['closeOnScroll'],
  );

  $form_core['closeOnVerticalDrag'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Close gallery when dragging vertically and when image is not zoomed'),
    '#description' => $t('Always false when mouse is used.'),
    '#default_value' => $form_core_defaults['closeOnVerticalDrag'],
  );

  $form_core['mouseUsed'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Mouse used'),
    '#description' => $t('Option allows you to predefine if mouse was used or not. Some PhotoSwipe feature depend on it, for example default UI left/right arrows will be displayed only after mouse is used.'),
    '#default_value' => $form_core_defaults['mouseUsed'],
  );

  $form_core['escKey'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Esc keyboard key to close PhotoSwipe'),
    '#default_value' => $form_core_defaults['escKey'],
  );

  $form_core['arrowKeys'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Keyboard left or right arrow key navigation'),
    '#default_value' => $form_core_defaults['arrowKeys'],
  );

  $form_core['history'] = array(
    '#type' => 'checkbox',
    '#title' => $t('History manipulation module'),
    '#default_value' => $form_core_defaults['history'],
  );

  $form_core['errorMsg'] = array(
    '#type' => 'textfield',
    '#title' => $t('Error message when image was not loaded'),
    '#description' => $t('%url% will be replaced by URL of image.'),
    '#default_value' => $form_core_defaults['errorMsg'],
  );

  // preload

  $form_core['mainClass'] = array(
    '#type' => 'textfield',
    '#title' => $t('Main class'),
    '#description' => $t('String with name of class that will be added to root element of PhotoSwipe (.pswp). Can contain multiple classes separated by space.'),
    '#default_value' => $form_core_defaults['mainClass'],
  );

  $form_core['focus'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Focus'),
    '#description' => $t("Will set focus on PhotoSwipe element after it's open."),
    '#default_value' => $form_core_defaults['focus'],
  );

  $form_core['modal'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Modal'),
    '#description' => $t('Controls whether PhotoSwipe should expand to take up the entire viewport. If false, the PhotoSwipe element will take the size of the positioned parent of the template. Take a look at <a href="@faq_url">the FAQ</a> for more information.', array('@faq_url' => 'http://photoswipe.com/documentation/faq.html#inline-gallery')),
    '#default_value' => $form_core_defaults['modal'],
  );

  $form['ikto_photoswipe_formatter_defaults']['ikto_photoswipe_formatter_defaults_default_ui'] = array(
    '#type'         => 'fieldset',
    '#title'        => $t('Default UI options'),
    '#collapsible'  => TRUE,
    '#collapsed'    => FALSE,
    '#tree'         => TRUE,
  );

  $form_default_ui = &$form['ikto_photoswipe_formatter_defaults']['ikto_photoswipe_formatter_defaults_default_ui'];
  $form_default_ui_defaults = ikto_photoswipe_get_global_options_default_ui();

  // barsSize

  $form_default_ui['timeToIdle'] = array(
    '#type' => 'textfield',
    '#title' => $t('Idle time (in milliseconds)'),
    '#description' => $t("Adds class pswp__ui--idle to pswp__ui element when mouse isn't moving for specified time."),
    '#default_value' => $form_default_ui_defaults['timeToIdle'],
    '#element_validate' => array('ikto_form_element_validate_integer_not_negative'),
  );

  $form_default_ui['timeToIdleOutside'] = array(
    '#type' => 'textfield',
    '#title' => $t('Idle time when mouse leaves the window (in milliseconds)'),
    '#description' => $t('Same as above, but this timer applies when mouse leaves the window.'),
    '#default_value' => $form_default_ui_defaults['timeToIdleOutside'],
    '#element_validate' => array('ikto_form_element_validate_integer_not_negative'),
  );

  $form_default_ui['loadingIndicatorDelay'] = array(
    '#type' => 'textfield',
    '#title' => $t('Loading indicator delay (in milliseconds)'),
    '#description' => $t('Delay until loading indicator is displayed.'),
    '#default_value' => $form_default_ui_defaults['loadingIndicatorDelay'],
    '#element_validate' => array('ikto_form_element_validate_integer_not_negative'),
  );

  $form_default_ui_elements = array(
    'closeEl' => $t('Close element'),
    'captionEl' => $t('Caption element'),
    'fullscreenEl' => $t('Fullscreen element'),
    'zoomEl' => $t('Zoom element'),
    'shareEl' => $t('Share element'),
    'counterEl' => $t('Counter element'),
    'arrowEl' => $t('Arrow element'),
    'preloaderEl' => $t('Preloader element'),
  );

  foreach ($form_default_ui_elements as $id => $title) {
    $form_default_ui[$id] = array(
      '#type' => 'checkbox',
      '#title' => $title,
      '#default_value' => $form_default_ui_defaults[$id],
    );
  }

  $form_default_ui['tapToClose'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Tap to close'),
    '#description' => $t('Tap on sliding area should close gallery.'),
    '#default_value' => $form_default_ui_defaults['tapToClose'],
  );

  $form_default_ui['tapToToggleControls'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Tap to toggle controls'),
    '#description' => $t('Tap should toggle visibility of controls.'),
    '#default_value' => $form_default_ui_defaults['tapToToggleControls'],
  );

  $form_default_ui['clickToCloseNonZoomable'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Click to close non zoomable'),
    '#description' => $t('Mouse click on image should close the gallery, only when image is smaller than size of the viewport.'),
    '#default_value' => $form_default_ui_defaults['clickToCloseNonZoomable'],
  );

  // closeElClasses

  $form_default_ui['indexIndicatorSep'] = array(
    '#type' => 'textfield',
    '#title' => $t('Separator for "1 of X" counter'),
    '#default_value' => $form_default_ui_defaults['indexIndicatorSep'],
  );

  // shareButtons

  $form['ikto_photoswipe_library'] = array(
    '#type'         => 'fieldset',
    '#title'        => $t('PhotoSwipe library'),
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );

  $form['ikto_photoswipe_library']['ikto_photoswipe_library_variant'] = array(
    '#type'           => 'radios',
    '#title'          => $t('PhotoSwipe library variant'),
    '#options'        => array(
      'source'    => $t('Source (development)'),
      'minified'  => $t('Minified (production)'),
    ),
    '#default_value'  => variable_get('ikto_photoswipe_library_variant', 'minified'),
  );

  $form['ikto_photoswipe_compat'] = array(
    '#type'         => 'fieldset',
    '#title'        => $t('Compatibility workarounds'),
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );

  $form['ikto_photoswipe_compat']['ikto_photoswipe_compat_slick'] = array(
    '#type' => 'checkbox',
    '#title' => $t('Slick carousel or slider'),
    '#description' => $t('Exclude gallery images inside <em>.slick-cloned</em> container'),
    '#default_value' => variable_get('ikto_photoswipe_compat_slick', FALSE),
  );

  return system_settings_form($form);
}
