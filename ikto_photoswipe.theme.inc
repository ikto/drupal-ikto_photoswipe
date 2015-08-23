<?php

function theme_ikto_photoswipe_field($vars) {
  $item = $vars['item'];
  $settings = $vars['display_settings'];

  $image = array(
    'path' => $item['uri'],
    'style_name' => $settings['default_image_style'],
  );

  $dimensions = array();
  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $dimensions['width'] = $item['width'];
    $image['height'] = $dimensions['height'] = $item['height'];
  }

  if ($style_name = $settings['photoswipe_image_style']) {
    $path_link = image_style_url($style_name, $image['path']);
    image_style_transform_dimensions($style_name, $dimensions);
  }
  else {
    $path_link = file_create_url($image['path']);
  }

  if (!empty($image['style_name'])) {
    $image = theme('image_style', $image);
  }
  else {
    $image = theme('image', $image);
  }

  $options_link = array(
    'html' => TRUE,
    'attributes' => array(
      'class'       => 'ikto-photoswipe',
      'data-width'  => $dimensions['width'],
      'data-height' => $dimensions['height'],
      'data-title'  => '',
    ),
  );

  return l($image, $path_link, $options_link);
}
