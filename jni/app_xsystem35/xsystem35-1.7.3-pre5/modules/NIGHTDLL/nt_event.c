#include "config.h"

#include <stdio.h>
#include <glib.h>

#include "portab.h"
#include "system.h"
#include "counter.h"
#include "menu.h"
#include "imput.h"
#include "nact.h"
#include "key.h"
#include "night.h"
#include "sprite.h"

/*
  Message���������Ԥ�����
*/
static void cb_waitkey_message(agsevent_t *e) {
	switch (e->type) {
	case AGSEVENT_BUTTON_RELEASE:
	case AGSEVENT_KEY_RELEASE:
		night.msg.cbrelease(e);
		break;
	case AGSEVENT_MOUSE_MOTION:
		night.msg.cbmove(e);
		break;
	}
}

/*
  WaitKeySimple��callback
*/
static void cb_waitkey_simple(agsevent_t *e) {
	switch (e->type) {
	case AGSEVENT_BUTTON_RELEASE:
	case AGSEVENT_KEY_RELEASE:
		night.waitkey = e->d3;
		break;
	}
}

/*
  ����� Window Open ���� callback
*/
static void cb_waitkey_selection(agsevent_t *e) {
	switch (e->type) {
	case AGSEVENT_BUTTON_RELEASE:
		night.sel.cbrelease(e);
		break;
		
	case AGSEVENT_MOUSE_MOTION:
		night.sel.cbmove(e);
		break;
	}
}

void ntev_callback(agsevent_t *e) {
	// menu open���̵��
	if (nact->popupmenu_opened) {
		return;
	}
	
	if (e->type == AGSEVENT_KEY_PRESS && e->d3 == KEY_CTRL) {
		night.waitskiplv = 2;
		night.waitkey = e->d3;
		return;
	}
	
	if (e->type == AGSEVENT_KEY_RELEASE && e->d3 == KEY_CTRL) {
		night.waitskiplv = 0;
		night.waitkey = e->d3;
		return;
	}
	
	switch (night.waittype) {
	case KEYWAIT_MESSAGE:
		cb_waitkey_message(e);
		break;
		
	case KEYWAIT_SIMPLE:
		cb_waitkey_simple(e);
		break;
		
	case KEYWAIT_SPRITE:
		cb_waitkey_sprite(e);
		break;
		
	case KEYWAIT_SELECT:
		cb_waitkey_selection(e);
		break;
		
	default:
		return;
	}
	
}

/*
  system35�Υᥤ��롼�פ���ǸƤФ�륳����Хå�
*/
void ntev_main() {
        // �ǥե���ȤΥ�����Хå��Τ�����������ɬ�פʤ�Τ���������
        if (nact->popupmenu_opened) {
                menu_gtkmainiteration();
                if (nact->is_quit) sys_exit(0);
        }
}