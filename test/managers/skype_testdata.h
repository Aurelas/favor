//
// Created by josh on 1/13/16.
// #sqlite3 main.db '.schema'

#ifndef FAVOR_SKYPE_TESTDATA_H_H
#define FAVOR_SKYPE_TESTDATA_H_H

#define SKYPE_SQLITE_SCHEMA "CREATE TABLE DbMeta (key TEXT NOT NULL PRIMARY KEY, value TEXT);"\
"CREATE TABLE AppSchemaVersion (ClientVersion TEXT NOT NULL, SQLiteSchemaVersion INTEGER NOT NULL, SchemaUpdateType INTEGER NOT NULL);"\
"CREATE TABLE Contacts (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, type INTEGER, skypename TEXT, pstnnumber TEXT, aliases TEXT, fullname TEXT, birthday INTEGER, gender INTEGER, languages TEXT, country TEXT, province TEXT, city TEXT, phone_home TEXT, phone_office TEXT, phone_mobile TEXT, emails TEXT, hashed_emails TEXT, homepage TEXT, about TEXT, avatar_image BLOB, mood_text TEXT, rich_mood_text TEXT, timezone INTEGER, capabilities BLOB, profile_timestamp INTEGER, nrof_authed_buddies INTEGER, ipcountry TEXT, avatar_timestamp INTEGER, mood_timestamp INTEGER, received_authrequest TEXT, authreq_timestamp INTEGER, lastonline_timestamp INTEGER, availability INTEGER, displayname TEXT, refreshing INTEGER, given_authlevel INTEGER, given_displayname TEXT, assigned_speeddial TEXT, assigned_comment TEXT, alertstring TEXT, lastused_timestamp INTEGER, authrequest_count INTEGER, assigned_phone1 TEXT, assigned_phone1_label TEXT, assigned_phone2 TEXT, assigned_phone2_label TEXT, assigned_phone3 TEXT, assigned_phone3_label TEXT, buddystatus INTEGER, isauthorized INTEGER, popularity_ord INTEGER, external_id TEXT, external_system_id TEXT, isblocked INTEGER, authorization_certificate BLOB, certificate_send_count INTEGER, account_modification_serial_nr INTEGER, saved_directory_blob BLOB, nr_of_buddies INTEGER, server_synced INTEGER, contactlist_track INTEGER, last_used_networktime INTEGER, authorized_time INTEGER, sent_authrequest TEXT, sent_authrequest_time INTEGER, sent_authrequest_serial INTEGER, buddyblob BLOB, cbl_future BLOB, node_capabilities INTEGER, revoked_auth INTEGER, added_in_shared_group INTEGER, in_shared_group INTEGER, authreq_history BLOB, profile_attachments BLOB, stack_version INTEGER, offline_authreq_id INTEGER, node_capabilities_and INTEGER, authreq_crc INTEGER, authreq_src INTEGER, pop_score INTEGER, authreq_nodeinfo BLOB, main_phone TEXT, unified_servants TEXT, phone_home_normalized TEXT, phone_office_normalized TEXT, phone_mobile_normalized TEXT, sent_authrequest_initmethod INTEGER, authreq_initmethod INTEGER, verified_email BLOB, verified_company BLOB, sent_authrequest_extrasbitmask INTEGER, liveid_cid TEXT, extprop_tags TEXT, extprop_away_since INTEGER);"\
"CREATE TABLE LegacyMessages (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER);"\
"CREATE TABLE Calls (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, begin_timestamp INTEGER, topic TEXT, is_muted INTEGER, is_unseen_missed INTEGER, host_identity TEXT, mike_status INTEGER, duration INTEGER, soundlevel INTEGER, access_token TEXT, active_members INTEGER, is_active INTEGER, name TEXT, video_disabled INTEGER, joined_existing INTEGER, server_identity TEXT, vaa_input_status INTEGER, is_incoming INTEGER, is_conference INTEGER, is_on_hold INTEGER, start_timestamp INTEGER, quality_problems TEXT, current_video_audience TEXT, premium_video_status INTEGER, premium_video_is_grace_period INTEGER, is_premium_video_sponsor INTEGER, premium_video_sponsor_list TEXT, old_members BLOB, partner_handle TEXT, partner_dispname TEXT, type INTEGER, status INTEGER, failurereason INTEGER, failurecode INTEGER, pstn_number TEXT, old_duration INTEGER, conf_participants BLOB, pstn_status TEXT, members BLOB, conv_dbid INTEGER);"\
"CREATE TABLE Accounts (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, status INTEGER, pwdchangestatus INTEGER, logoutreason INTEGER, commitstatus INTEGER, suggested_skypename TEXT, skypeout_balance_currency TEXT, skypeout_balance INTEGER, skypeout_precision INTEGER, skypein_numbers TEXT, subscriptions TEXT, cblsyncstatus INTEGER, offline_callforward TEXT, chat_policy INTEGER, skype_call_policy INTEGER, pstn_call_policy INTEGER, avatar_policy INTEGER, buddycount_policy INTEGER, timezone_policy INTEGER, webpresence_policy INTEGER, phonenumbers_policy INTEGER, voicemail_policy INTEGER, authrequest_policy INTEGER, ad_policy INTEGER, partner_optedout TEXT, service_provider_info TEXT, registration_timestamp INTEGER, nr_of_other_instances INTEGER, partner_channel_status TEXT, flamingo_xmpp_status INTEGER, federated_presence_policy INTEGER, liveid_membername TEXT, roaming_history_enabled INTEGER, cobrand_id INTEGER, owner_under_legal_age INTEGER, type INTEGER, skypename TEXT, pstnnumber TEXT, fullname TEXT, birthday INTEGER, gender INTEGER, languages TEXT, country TEXT, province TEXT, city TEXT, phone_home TEXT, phone_office TEXT, phone_mobile TEXT, emails TEXT, homepage TEXT, about TEXT, profile_timestamp INTEGER, received_authrequest TEXT, displayname TEXT, refreshing INTEGER, given_authlevel INTEGER, aliases TEXT, authreq_timestamp INTEGER, mood_text TEXT, timezone INTEGER, nrof_authed_buddies INTEGER, ipcountry TEXT, given_displayname TEXT, availability INTEGER, lastonline_timestamp INTEGER, capabilities BLOB, avatar_image BLOB, assigned_speeddial TEXT, lastused_timestamp INTEGER, authrequest_count INTEGER, assigned_comment TEXT, alertstring TEXT, avatar_timestamp INTEGER, mood_timestamp INTEGER, rich_mood_text TEXT, synced_email BLOB, set_availability INTEGER, options_change_future BLOB, cbl_profile_blob BLOB, authorized_time INTEGER, sent_authrequest TEXT, sent_authrequest_time INTEGER, sent_authrequest_serial INTEGER, buddyblob BLOB, cbl_future BLOB, node_capabilities INTEGER, node_capabilities_and INTEGER, revoked_auth INTEGER, added_in_shared_group INTEGER, in_shared_group INTEGER, authreq_history BLOB, profile_attachments BLOB, stack_version INTEGER, offline_authreq_id INTEGER, verified_email BLOB, verified_company BLOB, uses_jcs INTEGER);"\
"CREATE TABLE Transfers (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, type INTEGER, partner_handle TEXT, partner_dispname TEXT, status INTEGER, failurereason INTEGER, starttime INTEGER, finishtime INTEGER, filepath TEXT, filename TEXT, filesize TEXT, bytestransferred TEXT, bytespersecond INTEGER, chatmsg_guid BLOB, chatmsg_index INTEGER, convo_id INTEGER, pk_id INTEGER, nodeid BLOB, last_activity INTEGER, flags INTEGER, old_status INTEGER, old_filepath INTEGER, accepttime INTEGER, parent_id INTEGER, offer_send_list TEXT);"\
"CREATE TABLE Voicemails (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, type INTEGER, partner_handle TEXT, partner_dispname TEXT, status INTEGER, failurereason INTEGER, subject TEXT, timestamp INTEGER, duration INTEGER, allowed_duration INTEGER, playback_progress INTEGER, convo_id INTEGER, chatmsg_guid BLOB, notification_id INTEGER, flags INTEGER, size INTEGER, path TEXT, failures INTEGER, vflags INTEGER, xmsg TEXT);"\
"CREATE TABLE Chats (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, name TEXT, options INTEGER, friendlyname TEXT, description TEXT, timestamp INTEGER, activity_timestamp INTEGER, dialog_partner TEXT, adder TEXT, type INTEGER, mystatus INTEGER, myrole INTEGER, posters TEXT, participants TEXT, applicants TEXT, banned_users TEXT, name_text TEXT, topic TEXT, topic_xml TEXT, guidelines TEXT, picture BLOB, alertstring TEXT, is_bookmarked INTEGER, passwordhint TEXT, unconsumed_suppressed_msg INTEGER, unconsumed_normal_msg INTEGER, unconsumed_elevated_msg INTEGER, unconsumed_msg_voice INTEGER, activemembers TEXT, state_data BLOB, lifesigns INTEGER, last_change INTEGER, first_unread_message INTEGER, pk_type INTEGER, dbpath TEXT, split_friendlyname TEXT, conv_dbid INTEGER);"\
"CREATE TABLE Messages (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, convo_id INTEGER, chatname TEXT, author TEXT, from_dispname TEXT, author_was_live INTEGER, guid BLOB, dialog_partner TEXT, timestamp INTEGER, type INTEGER, sending_status INTEGER, consumption_status INTEGER, edited_by TEXT, edited_timestamp INTEGER, param_key INTEGER, param_value INTEGER, body_xml TEXT, identities TEXT, reason TEXT, leavereason INTEGER, participant_count INTEGER, error_code INTEGER, chatmsg_type INTEGER, chatmsg_status INTEGER, body_is_rawxml INTEGER, oldoptions INTEGER, newoptions INTEGER, newrole INTEGER, pk_id INTEGER, crc INTEGER, remote_id INTEGER, call_guid TEXT);"\
"CREATE TABLE ContactGroups (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, type INTEGER, custom_group_id INTEGER, given_displayname TEXT, nrofcontacts INTEGER, nrofcontacts_online INTEGER, given_sortorder INTEGER, type_old INTEGER, proposer TEXT, description TEXT, associated_chat TEXT, members TEXT, cbl_id INTEGER, cbl_blob BLOB, fixed INTEGER, keep_sharedgroup_contacts INTEGER, chats TEXT, extprop_is_hidden INTEGER, extprop_sortorder_value INTEGER, extprop_is_expanded INTEGER);"\
"CREATE TABLE Videos (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, status INTEGER, error TEXT, debuginfo TEXT, dimensions TEXT, media_type INTEGER, duration_1080 INTEGER, duration_720 INTEGER, duration_hqv INTEGER, duration_vgad2 INTEGER, duration_ltvgad2 INTEGER, timestamp INTEGER, hq_present INTEGER, duration_ss INTEGER, ss_timestamp INTEGER, convo_id INTEGER, device_path TEXT);"\
"CREATE TABLE SMSes (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, type INTEGER, outgoing_reply_type INTEGER, status INTEGER, failurereason INTEGER, error_category INTEGER, is_failed_unseen INTEGER, timestamp INTEGER, price INTEGER, price_precision INTEGER, price_currency TEXT, reply_to_number TEXT, target_numbers TEXT, target_statuses BLOB, body TEXT, chatmsg_id INTEGER, identity TEXT, notification_id INTEGER, event_flags INTEGER, reply_id_number TEXT, convo_name TEXT);"\
"CREATE TABLE CallMembers (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, identity TEXT, dispname TEXT, languages TEXT, call_duration INTEGER, price_per_minute INTEGER, price_precision INTEGER, price_currency TEXT, payment_category TEXT, type INTEGER, status INTEGER, failurereason INTEGER, sounderror_code INTEGER, soundlevel INTEGER, pstn_statustext TEXT, pstn_feedback TEXT, forward_targets TEXT, forwarded_by TEXT, debuginfo TEXT, videostatus INTEGER, target_identity TEXT, mike_status INTEGER, is_read_only INTEGER, quality_status INTEGER, call_name TEXT, transfer_status INTEGER, transfer_active INTEGER, transferred_by TEXT, transferred_to TEXT, guid TEXT, next_redial_time INTEGER, nrof_redials_done INTEGER, nrof_redials_left INTEGER, transfer_topic TEXT, real_identity TEXT, start_timestamp INTEGER, is_conference INTEGER, quality_problems TEXT, identity_type INTEGER, country TEXT, creation_timestamp INTEGER, stats_xml TEXT, is_premium_video_sponsor INTEGER, is_multiparty_video_capable INTEGER, recovery_in_progress INTEGER, nonse_word TEXT, nr_of_delivered_push_notifications INTEGER, call_session_guid TEXT, version_string TEXT, ip_address TEXT, is_video_codec_compatible INTEGER, is_seamlessly_upgraded_call INTEGER, pk_status INTEGER, call_db_id INTEGER, prime_status INTEGER);"\
"CREATE TABLE ChatMembers (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, chatname TEXT, identity TEXT, role INTEGER, is_active INTEGER, cur_activities INTEGER, adder TEXT);"\
"CREATE TABLE Alerts (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, timestamp INTEGER, partner_name TEXT, is_unseen INTEGER, partner_id INTEGER, partner_event TEXT, partner_history TEXT, partner_header TEXT, partner_logo TEXT, meta_expiry INTEGER, message_header_caption TEXT, message_header_title TEXT, message_header_subject TEXT, message_header_cancel TEXT, message_header_later TEXT, message_content TEXT, message_footer TEXT, message_button_caption TEXT, message_button_uri TEXT, message_type INTEGER, window_size INTEGER, chatmsg_guid BLOB, notification_id INTEGER, event_flags INTEGER);"\
"CREATE TABLE Conversations (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, identity TEXT, type INTEGER, live_host TEXT, live_start_timestamp INTEGER, live_is_muted INTEGER, alert_string TEXT, is_bookmarked INTEGER, is_blocked INTEGER, given_displayname TEXT, displayname TEXT, local_livestatus INTEGER, inbox_timestamp INTEGER, inbox_message_id INTEGER, last_message_id INTEGER, unconsumed_suppressed_messages INTEGER, unconsumed_normal_messages INTEGER, unconsumed_elevated_messages INTEGER, unconsumed_messages_voice INTEGER, active_vm_id INTEGER, context_horizon INTEGER, consumption_horizon INTEGER, last_activity_timestamp INTEGER, active_invoice_message INTEGER, spawned_from_convo_id INTEGER, pinned_order INTEGER, creator TEXT, creation_timestamp INTEGER, my_status INTEGER, opt_joining_enabled INTEGER, opt_access_token TEXT, opt_entry_level_rank INTEGER, opt_disclose_history INTEGER, opt_history_limit_in_days INTEGER, opt_admin_only_activities INTEGER, passwordhint TEXT, meta_name TEXT, meta_topic TEXT, meta_guidelines TEXT, meta_picture BLOB, picture TEXT, is_p2p_migrated INTEGER, premium_video_status INTEGER, premium_video_is_grace_period INTEGER, guid TEXT, dialog_partner TEXT, meta_description TEXT, premium_video_sponsor_list TEXT, mcr_caller TEXT, chat_dbid INTEGER, history_horizon INTEGER, history_sync_state TEXT, thread_version TEXT, consumption_horizon_set_at INTEGER, alt_identity TEXT, in_migrated_thread_since INTEGER, extprop_windowpos_x INTEGER, extprop_windowpos_y INTEGER, extprop_windowpos_w INTEGER, extprop_windowpos_h INTEGER, extprop_window_roster_visible INTEGER, extprop_window_splitter_layout TEXT, extprop_hide_from_history INTEGER, extprop_window_detached INTEGER);"\
"CREATE TABLE Participants (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, convo_id INTEGER, identity TEXT, rank INTEGER, requested_rank INTEGER, text_status INTEGER, voice_status INTEGER, video_status INTEGER, live_identity TEXT, live_price_for_me TEXT, live_fwd_identities TEXT, live_start_timestamp INTEGER, sound_level INTEGER, debuginfo TEXT, next_redial_time INTEGER, nrof_redials_left INTEGER, last_voice_error TEXT, quality_problems TEXT, live_type INTEGER, live_country TEXT, transferred_by TEXT, transferred_to TEXT, adder TEXT, last_leavereason INTEGER, is_premium_video_sponsor INTEGER, is_multiparty_video_capable INTEGER, live_identity_to_use TEXT, livesession_recovery_in_progress INTEGER, is_multiparty_video_updatable INTEGER, live_ip_address TEXT, is_video_codec_compatible INTEGER, is_seamlessly_upgraded_call INTEGER, real_identity TEXT, adding_in_progress_since INTEGER);"\
"CREATE TABLE VideoMessages (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, qik_id BLOB, attached_msg_ids TEXT, sharing_id TEXT, status INTEGER, vod_status INTEGER, vod_path TEXT, local_path TEXT, public_link TEXT, progress INTEGER, title TEXT, description TEXT, author TEXT, creation_timestamp INTEGER, type TEXT);"\
"CREATE TABLE MediaDocuments (id INTEGER NOT NULL PRIMARY KEY, is_permanent INTEGER, storage_document_id INTEGER, status INTEGER, doc_type INTEGER, uri TEXT);"\
"CREATE INDEX IX_Contacts_skypename ON Contacts (skypename);"\
"CREATE INDEX IX_Contacts_buddystatus ON Contacts (buddystatus);"\
"CREATE INDEX IX_Calls_name ON Calls (name);"\
"CREATE INDEX IX_Calls_is_unseen_missed ON Calls (is_unseen_missed);"\
"CREATE INDEX IX_Calls_begin_timestamp ON Calls (begin_timestamp);"\
"CREATE INDEX IX_Accounts_skypename ON Accounts (skypename);"\
"CREATE INDEX IX_Transfers_type ON Transfers (type);"\
"CREATE INDEX IX_Transfers_partner_handle ON Transfers (partner_handle);"\
"CREATE INDEX IX_Transfers_status ON Transfers (status);"\
"CREATE INDEX IX_Transfers_chatmsg_guid ON Transfers (chatmsg_guid);"\
"CREATE INDEX IX_Voicemails_type ON Voicemails (type);"\
"CREATE INDEX IX_Voicemails_partner_handle ON Voicemails (partner_handle);"\
"CREATE INDEX IX_Voicemails_status ON Voicemails (status);"\
"CREATE INDEX IX_Voicemails_notification_id ON Voicemails (notification_id);"\
"CREATE INDEX IX_Voicemails_chatmsg_guid ON Voicemails (chatmsg_guid);"\
"CREATE INDEX IX_Voicemails_flags ON Voicemails (flags);"\
"CREATE INDEX IX_Chats_name ON Chats (name);"\
"CREATE INDEX IX_Chats_type ON Chats (type);"\
"CREATE INDEX IX_Chats_mystatus ON Chats (mystatus);"\
"CREATE INDEX IX_Chats_activity_timestamp ON Chats (activity_timestamp);"\
"CREATE INDEX IX_Chats_participants ON Chats (participants);"\
"CREATE INDEX IX_Chats_is_bookmarked ON Chats (is_bookmarked);"\
"CREATE INDEX IX_Chats_lifesigns ON Chats (lifesigns);"\
"CREATE INDEX IX_Chats_first_unread_message ON Chats (first_unread_message);"\
"CREATE INDEX IX_Messages_convo_id_timestamp_consumption_status_sending_status ON Messages (convo_id, timestamp, consumption_status, sending_status);"\
"CREATE INDEX IX_Messages_call_guid ON Messages (call_guid);"\
"CREATE INDEX IX_Messages_timestamp_chatname ON Messages (timestamp, chatname);"\
"CREATE INDEX IX_Messages_timestamp_convo_id_type ON Messages (timestamp, convo_id, type);"\
"CREATE INDEX IX_Messages_remote_id ON Messages (remote_id);"\
"CREATE INDEX IX_ContactGroups_given_displayname ON ContactGroups (given_displayname);"\
"CREATE INDEX IX_SMSes_type ON SMSes (type);"\
"CREATE INDEX IX_SMSes_target_numbers ON SMSes (target_numbers);"\
"CREATE INDEX IX_SMSes_status ON SMSes (status);"\
"CREATE INDEX IX_SMSes_notification_id ON SMSes (notification_id);"\
"CREATE INDEX IX_SMSes_chatmsg_id ON SMSes (chatmsg_id);"\
"CREATE INDEX IX_CallMembers_call_name ON CallMembers (call_name);"\
"CREATE INDEX IX_CallMembers_identity ON CallMembers (identity);"\
"CREATE INDEX IX_ChatMembers_chatname ON ChatMembers (chatname);"\
"CREATE INDEX IX_ChatMembers_identity ON ChatMembers (identity);"\
"CREATE INDEX IX_Alerts_timestamp ON Alerts (timestamp);"\
"CREATE INDEX IX_Alerts_notification_id ON Alerts (notification_id);"\
"CREATE INDEX IX_Alerts_chatmsg_guid ON Alerts (chatmsg_guid);"\
"CREATE INDEX IX_Conversations_type ON Conversations (type);"\
"CREATE INDEX IX_Conversations_identity ON Conversations (identity);"\
"CREATE INDEX IX_Conversations_alt_identity ON Conversations (alt_identity);"\
"CREATE INDEX IX_Conversations_inbox_timestamp ON Conversations (inbox_timestamp);"\
"CREATE INDEX IX_Participants_convo_id ON Participants (convo_id);"\
"CREATE INDEX IX_Participants_identity ON Participants (identity);"\
"CREATE INDEX IX_VideoMessages_qik_id ON VideoMessages (qik_id);"


#endif //FAVOR_SKYPE_TESTDATA_H_H
