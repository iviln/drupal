<?php

/**
 * Реализация hook_block_info().
 */

function social_icons_block_info() {
    
    $blocks['social_icons'] = array(
      'info'    => t('Social Icons'),
      'status'  => FALSE,
      'weight'  => 0, 
    );
    return $blocks;
}

/**
 * Реализация hook_block_configure().
 */

function social_icons_block_configure($delta = '') {
  $form= array();
  switch ($delta) {
    case 'social_icons':
      $form['social_icons_width'] = array(
        '#title' =>t('Width for icon.'),
        '#type' => 'textfield',
        '#size' => 3,
        '#descritpion' => t('Default value 50px'),
        '#default' => variable_get('social_icons_width', 50),
        '#suffix' => 'px',
      );
      $form['social_icons_height'] = array(
        '#title' => t('Height for icon.'),
        '#type' => 'textfield',
        '#size' => 3,
        '#descritpion' => t('Default value 50px'),
        '#default' => variable_get('social_icons_height', 50),
        '#suffix' => 'px',
      );
      $form['social_icons_position'] = array(
        '#title' => t('Position'),
        '#type' => 'select',
        '#options' => array(
          'gorisontal' => t('Gorisontal'),
          'vertical' => t('Vertical'),
        ),
        '#size' => 3,
        '#descritpion' => t('Default value 50px'),
        '#default' => variable_get('social_icons_position', 'vertical'),
        
      );
      break;
  }
  return $form;
}

function social_icons_block_view($delta = '') {
		
	switch ($delta) {
		case 'social_icons':
		    $block['subject'] = t('Социальные сети');
			$block['content'] = social_icons_block_contents($delta);			
			return $block;	
            break;
      }
}

function social_icons_block_contents($delta) { 
    $social_icons = db_select('social_icons', 'si')
    ->fields('si', array('id'))
    ->orderBy('si.id')
    ->execute();
    $rows = array();

  foreach ($social_icons as $id) {
    $entity = social_icons_load($id->id);
      $rows[] = array(
      l(theme_image(social_icons_image_array($entity->icon)), $entity->link, array('html' => true)),
      );
  
  $rows_l = array('rows' => $rows);
  $output = theme('table',$rows_l);
  } 
  return $output;
}


