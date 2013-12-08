<?php

/**
 * @file
 * Provides functions for setting up the site wide status.
 */


/**
 * Author : Stephen Blinkhorne
 *  stephen.blinkhorne@talquin.com
 * 
 * Created 30th July 2013
 * 
 */

/**
 * Show the form to allow the user to change the settings.
 *
 * @param 
 *   none
 *
 * @return
 *   Form array to be rendered
 */
function film_links_settings($form, &$form_state) {

  // Give some information on the setting up process.
  // Might need to add code to prevent or warn user if they decide to change it

//  $output['title'] = array(
//      '#markup' => t('Film link set up'),
//      '#weight' => 1,
//      '#prefix' => '<h1>',
//      '#suffix' => '</h1>',        
//    );
//
//  $output['description'] = array(
//      '#markup' => 'Film set up options.',
//  
//  );
  
  $buttons = variable_get('film_general_buttons', array(
    'people_edit_crew' => '',
    'people_edit_cast' => '',
    'film_edit_crew' => '',
    'film_edit_cast' => '',
    'organisation_edit' => '',
  ));

  $form['film_general_buttons'] = array(
    '#prefix' => '<a id="buttons"></a>',
    '#type' => 'fieldset',
    '#title' => t('Buttons'),
    '#description' => t('The text sections required for the introductory page of the eligibility form.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,

    'people_edit_crew' => array(
      '#type' => 'textfield',
      '#title' => t('People edit crew'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['people_edit_crew'])?$buttons['people_edit_crew']:'',
    ),

    'people_edit_cast' => array(
      '#type' => 'textfield',
      '#title' => t('People edit cast'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['people_edit_cast'])?$buttons['people_edit_cast']:'',
    ),
    
    'film_edit_crew' => array(
      '#type' => 'textfield',
      '#title' => t('Film edit crew'),
  //    '#description' => t('Enter the text dealing with the research being carried out.'),
      '#default_value' => !empty($buttons['film_edit_crew'])?$buttons['film_edit_crew']:'',
    ),

    'film_edit_cast' => array(
      '#type' => 'textfield',
      '#title' => t('Film edit cast'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['film_edit_cast'])?$buttons['film_edit_cast']:'',
    ),    
    
    'organisation_edit' => array(
      '#type' => 'textfield',
      '#title' => t('Organisation edit'),
  //    '#description' => t('Enter the invitation text.'),
      '#default_value' => !empty($buttons['organisation_edit'])?$buttons['organisation_edit']:'',
    ),        
  );


  return system_settings_form($form);
}

