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
function film_links_settings() {

  // Give some information on the setting up process.
  // Might need to add code to prevent or warn user if they decide to change it

  $output['title'] = array(
      '#markup' => t('Film link set up'),
      '#weight' => 1,
      '#prefix' => '<h1>',
      '#suffix' => '</h1>',        
    );

  $output['description'] = array(
      '#markup' => 'Film set up options.',
  
  );
  
  $film_links_setting_form = drupal_get_form('film_links_setting_form');

  $output['form'] = array(
      '#type' => 'item',
      '#markup' => drupal_render($film_links_setting_form),
      '#weight' => 5,
  );

  return $output;
}


/*
 *
 */
//function film_links_role_settings() {
//
//  // Give some information on the setting up process.
//  // Might need to add code to prevent or warn user if they decide to change it
//  $message  = '<h1>Roles</h1> ';
//  //$message .= 'Please select the default status for the site.<br>';
//
//  $output['title'] = array(
//        '#markup' => t('Roles2'),
//        //'#weight' => 1,
//        '#prefix' => '<h1>',
//        '#suffix' => '</h1>',
//      );
//
//  $output['form'] = array(
//      '#type' => 'item',
//      '#markup' => l(t('Add role'),'admin/config/film_links/settings/roles/add'),
//     // '#weight' => -100,
//  );
//
//
//  $output['roles'] = _film_links_get_roles_table();
//  return $output;
//}


/*
 *
 */
function film_links_role_add($form,$form_state) {

  // Give some information on the setting up process.
  // Might need to add code to prevent or warn user if they decide to change it
  $form['title'] = array(
        '#markup' => t('Roles'),
        //'#weight' => 1,
        '#prefix' => '<h1>',
        '#suffix' => '</h1>',
      );

  $form['description'] = array(
    '#markup' => t("Enter the name of the role to be added. If a role already exists you won't be allowed to add it"),
  );
    
  $form['field_role_name'] = array(
    '#type' => 'textfield', 
    '#title' => t('Role'),  
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );
  
  $form['field_character'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Show character'), 
  );  
  
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
    
  $form['roles'] = _film_links_get_roles_table();
  return $form;
}


function _film_links_get_roles_table() {
  $header = array(
    array('data' => t('Role'), 'field' => 'role'),
    array('data' => t('Character'), 'field' => 'character'),
    array('data' => ' ','field'=>'edit'),
    array('data' => ' ','field'=>'delete'),
  );

  $result = _film_links_get_roles(NULL);

  $rows = array();
  foreach($result as $row) {

    $rows_array = array();

    if ($row->film_character == 1) {
      $character = '<img src="/'.drupal_get_path('module','film_links'). '/image/tick.png" style="width:15px; height:15px;">';
      
    } else {
      $character = '';
    }

    $rows_array['name'] = l($row->name,'admin/config/film_links/settings/subroles/' . $row->rid);
    $rows_array['character'] = $character;
    $rows_array['edit'] = l('Edit','admin/config/film_links/settings/roles/edit/' . $row->rid);
    $rows_array['delete'] = l('Delete','admin/config/film_links/settings/roles/delete/' . $row->rid);

    $rows[] = $rows_array;
  }
  
  // Create a render array ($build) which will be themed as a table with a
  // pager.
  $output['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no roles.'),
  );
  
  return $output;
}

/**
 * Form to allow the user to set the global status.
 *
 * @param 
 *
 * @return
 *   Form array.
 */
function film_links_setting_form($form, &$form_state) {

  $form = array();

//  // Provide the list of options.
//  $form['setting'] = array(
//      '#type' => 'select',
//      '#title' => t('User status'),
//      '#options' => user_status_get_options(),
//      '#weight' => 2,      
//  );
  
  $form['action'] = array (
      '#type' => 'container',
      '#prefix' => '<div id="tab-buttons">',
      '#suffix' => '</div>',
      '#weight' => 10,      
  );

  // Add the submit button so we can process the response.
  $form['action']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('film_links_setting_submit'),
      
  );

  return $form;
}


/*
 * We save the item to the database
 */
function _film_links_role_save($role_name,$role_parent_id = NULL,$character = 0) {
  //
  $query = db_insert('film_link_role');
  $query->fields(
    array (
      'pid' => $role_parent_id,
      'name' => $role_name,
      'deleted' => 0,
      'film_character' => $character,
    )
  );
  try {
    $query->execute();
  } catch (Exception $e) {
    drupal_set_message(t('An error occurred inserting a role item. Check the log files for more information'),'error');
    watchdog('film_links','Error inserting item : ' . $e,NULL,WATCHDOG_ERROR);      
    return FALSE;
  }
  return TRUE;      
}

/*
 * Update the current role item
 */ 
function _film_links_role_update($role_id,$name,$character = 0) {
  $query = db_update('film_link_role');
  $query->fields(
      array(
        'name' => $name,
        'film_character' => $character,
      )
    );
  $query->condition('rid',$role_id,'=');

  try {
    $query->execute();
  } catch (Exception $e) {
    drupal_set_message(t('An error occurred updating a role item. Check the log files for more information'),'error');
    watchdog('film_links','Error updating item : ' . $e,NULL,WATCHDOG_ERROR);      
    return FALSE;
  }
  return TRUE;
}

/*
 * we delete all the roles and the sub roles
 */
function _film_links_role_delete($role_id) {
  // First we delete all the sub 
  // We need to make sure we don't delete everything which is the case if the 
  // role id is NULL
  if (!empty($role_id)) {
    $query = db_delete('film_link_role');
    $query->condition('pid',$role_id,'=');

    try {
      $query->execute();
    } catch (Exception $e) {
      drupal_set_message(t('An error occurred deleting a role item. Check the log files for more information'),'error');
      watchdog('film_links','Error deleting item : ' . $e,NULL,WATCHDOG_ERROR);      
      return FALSE;
    }
  }
  // Now we delete the main roles.
  $query = db_delete('film_link_role');
  $query->condition('rid',$role_id,'=');

  try {
    $query->execute();
  } catch (Exception $e) {
    drupal_set_message(t('An error occurred deleting a role item. Check the log files for more information'),'error');
    watchdog('film_links','Error deleting item : ' . $e,NULL,WATCHDOG_ERROR);      
    return FALSE;
  }  
  return TRUE;
}

/*
 * Check to see if the role already exists
 * Return TRUE if it does exists
 * Return array of field names and help text
 */
function _film_links_role_exists($role_name, $parent_id = NULL,$ignore_rid = NULL) {
  $query = db_select('film_link_role', 'r');
  $query->condition('r.name',$role_name,'=');
  if(!empty($parent_id)) {
    $query->condition('r.pid',$parent_id,'=');
  } else {
    $query->isNull('r.pid');    
  }
  
  if (!empty($ignore_rid)) {
    $query->condition('r.rid',$ignore_rid,'<>');
  }
  
  $query->fields('r',array('rid'));
 
  $result = $query->execute();
  
  $item_found = FALSE;
  foreach($result as $row) {
    $item_found = TRUE;
  }
  
  return $item_found;
}


/*
 * Get a list of roles in the system
 * If the $rid parameter is NULL then we get all the main roles otherwise 
 * we get the sub roles whose parent matches the $rid value.
 */
function _film_links_get_roles($rid = NULL) {
  $query = db_select('film_link_role','r');
  
  // might not need the following so will need to test it.
  if (!empty($rid)) {
    // We are looking for all the sub roles
    $query->condition('r.pid',$rid,'=');
  } else {
    // we are getting all the main roles.
    $query->isNull('r.pid');    
  }
  
  $query->fields('r', array('rid','pid','name','film_character'));
  
  $result = $query->execute();

  return $result;
}



/**
 * Process the response from the form submit.
 * 
 * We will store the user's selection in the database.
 *
 * @param 
 * 
 * @return
 *   Form array.
 */
function film_links_setting_submit($form,&$form_state) {
/*
  // Save the global response to the database
  if (!empty($form_state['values']['setting'])) {
    $return_value = _user_status_default_insert($form_state['values']['setting']);

    if ($return_value <> NULL) {
      $status_name = _get_user_status($form_state['values']['setting']);
      drupal_set_message('Your user status <strong>' . $status_name . '</strong> has been saved');
    }
  }
  */
}

/**
 * Process the response from the form submit.
 * 
 * We will store the user's selection in the database.
 *
 * @param 
 * 
 * @return
 *   Form array.
 */
function film_links_role_submit($form,&$form_state) {
  dpm($form);
  dpm($form_state);
/*
  // Save the global response to the database
  if (!empty($form_state['values']['setting'])) {
    $return_value = _user_status_default_insert($form_state['values']['setting']);

    if ($return_value <> NULL) {
      $status_name = _get_user_status($form_state['values']['setting']);
      drupal_set_message('Your user status <strong>' . $status_name . '</strong> has been saved');
    }
  }
  */
}


function film_links_role_add_validate($form, &$form_state) {
  // Check to make sure the role doesn't currently exist
 
  if (empty($form_state['values']['field_role_name'])) {
    form_set_error('field_role_name', t('Please fill in the name of the role.'));
  } else {
    // Now check to see if the name already exists
    $role_name = $form_state['values']['field_role_name'];

    if (_film_links_role_exists($role_name, NULL) == TRUE) {
      form_set_error('field_role_name', t('The role already exists.'));
    }
  }
}

function film_links_role_add_submit($form,&$form_state) {
  $role_name = $form_state['values']['field_role_name'];
  $character = $form_state['values']['field_character'];
  _film_links_role_save($role_name,NULL,$character);
}

/*
 * $item 
 */
function film_links_role_edit($form, $form_state, $role_id = NULL) {
  
  $role_details = film_links_get_role_details($role_id);
  $role_name = $role_details['name'];
  $character = $role_details['film_character'];
  
  $form['title'] = array(
    '#markup' => 'Role Edit',
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',      
  );

  $form['field_role_name'] = array(
    '#type' => 'textfield', 
    '#title' => t('Role'),  
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
    '#default_value' => $role_name,
  );
  
  $form['field_character'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Show character'),  
    '#default_value' => $character,
  );  
  
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['rid'],
  );
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['pid'],
  );
    
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}



function film_links_role_edit_validate($form, &$form_state) {
  $role_name = $form_state['values']['field_role_name'];
  $parent_id = $form_state['values']['pid'];
  $role_id = $form_state['values']['rid'];

  if (_film_links_role_exists($role_name, $parent_id,$role_id) == TRUE) {
      form_set_error('field_role_name', t('The role already exists.'));  
  }  
}


function film_links_role_edit_submit($form, &$form_state) {
  $role_id = $form_state['values']['rid'];
  $name = $form_state['values']['field_role_name'];
  $character = $form_state['values']['field_character'];
  
  if (_film_links_role_update($role_id,$name,$character) == TRUE) {
    drupal_set_message('Role ' . $name . ' has been successfully changed on the system.');
  }
  $form_state['redirect'] = 'admin/config/film_links/settings/roles';
}

function film_links_role_delete($form, $form_state, $role_id = NULL) {
  
  $role_details = film_links_get_role_details($role_id);
  $role_name = $role_details['name'];
  
  $form['title'] = array(
    '#markup' => 'Role Delete',
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',      
  );

  $form['description'] = array(
    '#markup' => '<p>Removing a role will remove all items associated with it. This operation cannot be undone once complete.</p>',
  );
  
  $form['field_role_name'] = array(
    '#markup' => '<p>Are you sure you want to delete the role <strong>' . $role_name . '</strong>?</p>',
  );
  
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['name'],
  );
    
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['rid'],
  );

  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['pid'],
  );
    
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );    
  
  return $form;
}

function film_links_role_delete_submit($form, &$form_state) {

  $role_id = $form_state['values']['rid'];
  $role_name = $form_state['values']['name'];

  if (_film_links_role_delete($role_id) == TRUE) {
    drupal_set_message('Role ' . $role_name . ' has been successfully removed from the system.');
  }
  $form_state['redirect'] = 'admin/config/film_links/settings/roles';
}

/******************************************************************************/

/*
 * Following section deals with sub roles. Might be worth putting into a 
 * separate file.
 */

/******************************************************************************/

/*
 * Display a list of sub roles for the role ID provided.
 * A new sub role can be added to the main role.
 */
function film_links_sub_roles($form, $form_state, $role_id = NULL) {
  
  $role_details = film_links_get_role_details($role_id);
  $role_name = $role_details['name'];
  $rid = $role_details['rid'];
  
  $form['title'] = array(
    '#markup' => 'Sub Roles for role ' . $role_name,
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',      
  );

  $form['title'] = array(
    '#markup' => l('Go back to roles',  'admin/config/film_links/settings/roles'),    
    '#prefix' => '<p>',
    '#suffix' => '</p>', 
  );
  
  $form['field_role_name'] = array(
    '#type' => 'textfield', 
    '#title' => t('New role'),  
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
  );
  
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $rid,
  );
  
  // The parent id (PID) should be NULL
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['pid'],
  );
    
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  
  $form['sub_roles'] = _film_links_get_sub_roles_table($rid);
  
  return $form;
}

function film_links_sub_roles_validate($form, &$form_state) {
  // Check to make sure the role doesn't currently exist
  if (empty($form_state['values']['field_role_name'])) {
    form_set_error('field_role_name', t('Please fill in the name of the role.'));
  } else {
    // Now check to see if the name already exists
    $role_name = $form_state['values']['field_role_name'];
    $parent_id = $form_state['values']['rid'];
    if (_film_links_role_exists($role_name, $parent_id) == TRUE) {
      form_set_error('field_role_name', t('The role already exists.'));
    }
  }
}

function film_links_sub_roles_submit($form,&$form_state) {
  $role_name = $form_state['values']['field_role_name'];
  $parent_id = $form_state['values']['rid'];
  _film_links_role_save($role_name,$parent_id);
}

function _film_links_get_sub_roles_table($rid = NULL) {
  $header = array(
    array('data' => t('Role')),
    array('data' => ' ','field'=>'edit'),
    array('data' => ' ','field'=>'delete'),
  );
    
  $result = _film_links_get_roles($rid);
  $rows = array();
  
  foreach($result as $row) {
    $row_array = array();
    $row_array['name'] = $row->name;
    $row_array['edit'] = l('Edit','admin/config/film_links/settings/subroles/edit/' . $row->rid);
    $row_array['delete'] = l('Delete','admin/config/film_links/settings/subroles/delete/' . $row->rid);
    $rows[] = $row_array;
  }
  
  // Create a render array ($build) which will be themed as a table with a
  // pager.
  $output['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no roles.'),
  );
  
  return $output;
}

/*
 * $item 
 */
function film_links_sub_role_edit($form, $form_state, $role_id = NULL) {
  dpm($role_id);
  
  $role_details = film_links_get_role_details($role_id);
  dpm($role_details);
  $role_name = $role_details['name'];
  
  $form['title'] = array(
    '#markup' => 'Role Edit',
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',      
  );

  $form['field_role_name'] = array(
    '#type' => 'textfield', 
    '#title' => t('Role'),  
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
    '#default_value' => $role_name,
  );
  
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['rid'],
  );
  
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['pid'],
  );
    
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}


/*
 * Check to make sure the name of the role doesn't already exist
 */
function film_links_sub_role_edit_validate($form, &$form_state) {
  $role_name = $form_state['values']['field_role_name'];
  $parent_id = $form_state['values']['pid'];

  if (_film_links_role_exists($role_name, $parent_id) == TRUE) {
      form_set_error('field_role_name', t('The role already exists.'));  
  }  
}


function film_links_sub_role_edit_submit($form, &$form_state) {
  dpm($form_state);
  $role_id = $form_state['values']['rid'];
  $parent_id = $form_state['values']['pid'];
  $name = $form_state['values']['field_role_name'];
  if (_film_links_role_update($role_id,$name) == TRUE) {
    drupal_set_message('Role ' . $name . ' has been successfully changed on the system.');
  }
  $form_state['redirect'] = 'admin/config/film_links/settings/subroles/' . $parent_id;  
}


function film_links_sub_role_delete($form, $form_state, $role_id = NULL) {
  
  $role_details = film_links_get_role_details($role_id);
  $role_name = $role_details['name'];
  
  $form['title'] = array(
    '#markup' => 'Role Delete',
    '#prefix' => '<h1>',
    '#suffix' => '</h1>',      
  );

  $form['description'] = array(
    '#markup' => '<p>Removing a role will remove all items associated with it. This operation cannot be undone once complete.</p>',
  );
  
  $form['field_role_name'] = array(
    '#markup' => '<p>Are you sure you want to delete the role <strong>' . $role_name . '</strong>?</p>',
  );
  
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['name'],
  );
    
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['rid'],
  );

  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $role_details['pid'],
  );
    
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );    
  
  return $form;
}

function film_links_sub_role_delete_submit($form, &$form_state) {
  $role_id = $form_state['values']['rid'];
  $role_name = $form_state['values']['name'];
  $parent_id = $form_state['values']['pid'];
  if (_film_links_role_delete($role_id) == TRUE) {
    drupal_set_message('Role ' . $role_name . ' has been successfully removed from the system.');
  }
  $form_state['redirect'] = 'admin/config/film_links/settings/subroles/' . $parent_id;
}
