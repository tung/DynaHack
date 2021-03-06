/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* DynaHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include "lev.h"	/* save & restore info */

static void setgemprobs(const d_level *dlev);
static void shuffle(int,int,boolean);
static void shuffle_all(void);
static boolean interesting_to_discover(int);
static void swap_armor(int,int,int);


static void setgemprobs(const d_level *dlev)
{
	int j, first, lev;

	if (dlev)
	    lev = (ledger_no(dlev) > maxledgerno())
				? maxledgerno() : ledger_no(dlev);
	else
	    lev = 0;
	first = bases[GEM_CLASS];

	for (j = 0; j < 9-lev/3; j++)
		objects[first+j].oc_prob = 0;
	first += j;
	if (first > LAST_GEM || objects[first].oc_class != GEM_CLASS ||
	    OBJ_NAME(objects[first]) == NULL) {
		raw_printf("Not enough gems? - first=%d j=%d LAST_GEM=%d\n",
			first, j, LAST_GEM);
	    }
	for (j = first; j <= LAST_GEM; j++)
		objects[j].oc_prob = (171+j-first)/(LAST_GEM+1-first);
}

/* shuffle descriptions on objects o_low to o_high */
static void shuffle(int o_low, int o_high, boolean domaterial)
{
	int i, j, num_to_shuffle;
	short sw;
	int color;

	for (num_to_shuffle = 0, j=o_low; j <= o_high; j++)
		if (!objects[j].oc_name_known) num_to_shuffle++;
	if (num_to_shuffle < 2) return;

	for (j=o_low; j <= o_high; j++) {
		if (objects[j].oc_name_known) continue;
		do
			i = j + rn2(o_high-j+1);
		while (objects[i].oc_name_known);
		sw = objects[j].oc_descr_idx;
		objects[j].oc_descr_idx = objects[i].oc_descr_idx;
		objects[i].oc_descr_idx = sw;
		sw = objects[j].oc_tough;
		objects[j].oc_tough = objects[i].oc_tough;
		objects[i].oc_tough = sw;
		color = objects[j].oc_color;
		objects[j].oc_color = objects[i].oc_color;
		objects[i].oc_color = color;

		/* shuffle material */
		if (domaterial) {
			sw = objects[j].oc_material;
			objects[j].oc_material = objects[i].oc_material;
			objects[i].oc_material = sw;
		}
	}
}


# define COPY_OBJ_DESCR(o_dst,o_src) \
			o_dst.oc_descr_idx = o_src.oc_descr_idx,\
			o_dst.oc_color = o_src.oc_color

void init_objects(void)
{
	int i, first, last, sum;
	char oclass;

	/* bug fix to prevent "initialization error" abort on Intel Xenix.
	 * reported by mikew@semike
	 */
	for (i = 0; i < MAXOCLASSES; i++)
		bases[i] = 0;
	/* initialize object descriptions */
	for (i = 0; i < NUM_OBJECTS; i++)
		objects[i].oc_name_idx = objects[i].oc_descr_idx = i;
	/* init base; if probs given check that they add up to 1000,
	   otherwise compute probs */
	first = 0;
	while ( first < NUM_OBJECTS ) {
		oclass = objects[first].oc_class;
		last = first+1;
		while (last < NUM_OBJECTS && objects[last].oc_class == oclass) last++;
		bases[(int)oclass] = first;

		if (oclass == GEM_CLASS) {
			setgemprobs(NULL);

			if (rn2(2)) { /* change turquoise from green to blue? */
			    COPY_OBJ_DESCR(objects[TURQUOISE],objects[SAPPHIRE]);
			}
			if (rn2(2)) { /* change aquamarine from green to blue? */
			    COPY_OBJ_DESCR(objects[AQUAMARINE],objects[SAPPHIRE]);
			}
			switch (rn2(4)) { /* change fluorite from violet? */
			    case 0:  break;
			    case 1:	/* blue */
				COPY_OBJ_DESCR(objects[FLUORITE],objects[SAPPHIRE]);
				break;
			    case 2:	/* white */
				COPY_OBJ_DESCR(objects[FLUORITE],objects[DIAMOND]);
				break;
			    case 3:	/* green */
				COPY_OBJ_DESCR(objects[FLUORITE],objects[EMERALD]);
				break;
			}
		}
	check:
		sum = 0;
		for (i = first; i < last; i++) sum += objects[i].oc_prob;
		if (sum == 0) {
			for (i = first; i < last; i++)
			    objects[i].oc_prob = (1000+i-first)/(last-first);
			goto check;
		}
		if (sum != 1000)
			raw_printf("init-prob error for class %d (%d%%)\n", oclass, sum);
		
		first = last;
	}
	/* shuffle descriptions */
	shuffle_all();
}

static void shuffle_all(void)
{
	int first, last, oclass, j;

	int num_scales = YELLOW_DRAGON_SCALES - GRAY_DRAGON_SCALES;

	for (oclass = 1; oclass < MAXOCLASSES; oclass++) {
		first = bases[oclass];
		last = first+1;
		while (last < NUM_OBJECTS && objects[last].oc_class == oclass)
			last++;

		if (OBJ_DESCR(objects[first]) != NULL &&
				oclass != TOOL_CLASS &&
				oclass != WEAPON_CLASS &&
				oclass != ARMOR_CLASS &&
				oclass != POTION_CLASS &&
				oclass != GEM_CLASS) {
			int j = last-1;

			if (oclass == AMULET_CLASS ||
				 oclass == SCROLL_CLASS ||
				 oclass == SPBOOK_CLASS) {
			    while (!objects[j].oc_magic || objects[j].oc_unique)
				j--;
			}

			/* non-magical amulets, scrolls, and spellbooks
			 * (ex. imitation Amulets, blank, scrolls of mail)
			 * and one-of-a-kind magical artifacts at the end of
			 * their class in objects[] have fixed descriptions.
			 */
			shuffle(first, j, TRUE);
		}
	}

	/* shuffle the helmets */
	shuffle(HELMET, HELM_OF_TELEPATHY, FALSE);

	/* shuffle the gloves */
	shuffle(LEATHER_GLOVES, GAUNTLETS_OF_DEXTERITY, FALSE);

	/* shuffle the cloaks */
	shuffle(CLOAK_OF_PROTECTION, CLOAK_OF_DISPLACEMENT, FALSE);

	/* shuffle the boots [if they change, update find_skates() below] */
	shuffle(SPEED_BOOTS, LEVITATION_BOOTS, FALSE);

	/* shuffle dragon scales / scale mail */
	for (j = num_scales; j >= 0; j--) {
	    int pos = rn2(j + 1);
	    swap_armor(j, pos, GRAY_DRAGON_SCALES);
	    swap_armor(j, pos, GRAY_DRAGON_SCALE_MAIL);
	}

	/* Shuffle the potions such that all descriptions that participate in
	 * color alchemy are mapped to potions that actually exist in the game,
	 * and certain good potions are guaranteed to map to secondary colors
	 * so that they can always be alchemized.
	 *
	 * Assumes:
	 * - POT_HEALING maps to the last secondary color description.
	 * - POT_FULL_HEALING maps to the last good potion guaranteed to be
	 *   mapped to a secondary color.
	 * - POT_POLYMORPH maps to the last color description.
	 * - water and beyond have fixed descs
	 * - POT_OIL is the last shuffled potion that isn't just a description.
	 */
	/* Shuffle secondary color potion descriptions. */
	shuffle(bases[POTION_CLASS], POT_HEALING, TRUE);
	/* Shuffle the other colors with no description guarantees. */
	shuffle(POT_FULL_HEALING + 1, POT_POLYMORPH, TRUE);
	/* Shuffle the non-color potion descriptions. */
	shuffle(POT_POLYMORPH + 1, POT_WATER - 1, TRUE);
	/* Shuffle potions that will exist with no description guarantees. */
	shuffle(POT_FULL_HEALING + 1, POT_OIL, TRUE);
}

/* swap two items of the same armor class;
 * currently name, description, color, price are swapped
 */
void swap_armor(int old_relative_position, int new_relative_position, int first)
{
	struct objclass tmp;

	int old_pos = old_relative_position + first;
	int new_pos = new_relative_position + first;

	tmp.oc_descr_idx = objects[old_pos].oc_descr_idx;
	tmp.oc_color     = objects[old_pos].oc_color;
	tmp.oc_cost      = objects[old_pos].oc_cost;

	objects[old_pos].oc_descr_idx = objects[new_pos].oc_descr_idx;
	objects[old_pos].oc_color     = objects[new_pos].oc_color;
	objects[old_pos].oc_cost      = objects[new_pos].oc_cost;

	objects[new_pos].oc_descr_idx = tmp.oc_descr_idx;
	objects[new_pos].oc_color     = tmp.oc_color;
	objects[new_pos].oc_cost      = tmp.oc_cost;
}

/* find the object index for snow boots; used [once] by slippery ice code */
int find_skates(void)
{
    int i;
    const char *s;

    for (i = SPEED_BOOTS; i <= LEVITATION_BOOTS; i++)
	if ((s = OBJ_DESCR(objects[i])) != 0 && !strcmp(s, "snow boots"))
	    return i;

    impossible("snow boots not found?");
    return -1;	/* not 0, or caller would try again each move */
}

void oinit(const struct level *lev)	/* level dependent initialization */
{
	setgemprobs(&lev->z);
}


static void saveobjclass(struct memfile *mf, struct objclass *ocl)
{
	int namelen = 0;
	unsigned int oflags;
	
	/*
	 * No mtag useful; object classes are always saved in the same
	 * order and there are always the same number of them.
	 */
	oflags = (ocl->oc_name_known		<< 31) |
		 (ocl->oc_merge			<< 30) |
		 (ocl->oc_uses_known		<< 29) |
		 (ocl->oc_pre_discovered	<< 28) |
		 (ocl->oc_magic			<< 27) |
		 (ocl->oc_charged		<< 26) |
		 (ocl->oc_unique		<< 25) |
		 (ocl->oc_nowish		<< 24) |
		 (ocl->oc_big			<< 23) |
		 (ocl->oc_tough			<< 22) |
		 (ocl->oc_dir			<< 20) |
		 (ocl->oc_material		<< 15);
	mwrite32(mf, oflags);
	mwrite16(mf, ocl->oc_name_idx);
	mwrite16(mf, ocl->oc_descr_idx);
	mwrite16(mf, ocl->oc_weight);
	mwrite16(mf, ocl->oc_prob);
	mwrite16(mf, ocl->oc_cost);
	mwrite16(mf, ocl->oc_nutrition);
	
	mwrite8(mf, ocl->oc_subtyp);
	mwrite8(mf, ocl->oc_oprop);
	mwrite8(mf, ocl->oc_class);
	mwrite8(mf, ocl->oc_delay);
	mwrite8(mf, ocl->oc_color);
	mwrite8(mf, ocl->oc_wsdam);
	mwrite8(mf, ocl->oc_wldam);
	mwrite8(mf, ocl->oc_oc1);
	mwrite8(mf, ocl->oc_oc2);
	
	/* as long as we use only one version of Hack we
	   need not save oc_name and oc_descr, but we must save
	   oc_uname for all objects */
	namelen = ocl->oc_uname ? strlen(ocl->oc_uname) + 1 : 0;
	mwrite32(mf, namelen);
	if (namelen)
	    mwrite(mf, ocl->oc_uname, namelen);
}


void savenames(struct memfile *mf)
{
	int i;

	mtag(mf, 0, MTAG_OCLASSES);
	mfmagic_set(mf, OCLASSES_MAGIC);
	for (i = 0; i < MAXOCLASSES; i++)
	    mwrite32(mf, bases[i]);

	for (i = 0; i < NUM_OBJECTS; i++)
	    mwrite32(mf, disco[i]);

	for (i = 0; i < NUM_OBJECTS; i++)
	    saveobjclass(mf, &objects[i]);
}


void freenames(void)
{
	int i;
	for (i = 0; i < NUM_OBJECTS; i++)
	    if (objects[i].oc_uname) {
		free(objects[i].oc_uname);
		objects[i].oc_uname = NULL;
	    }
}


static void restobjclass(struct memfile *mf, struct objclass *ocl)
{
	int namelen;
	unsigned int oflags;
	
	oflags = mread32(mf);
	ocl->oc_name_known = (oflags >> 31) & 1;
	ocl->oc_merge = (oflags >> 30) & 1;
	ocl->oc_uses_known = (oflags >> 29) & 1;
	ocl->oc_pre_discovered = (oflags >> 28) & 1;
	ocl->oc_magic = (oflags >> 27) & 1;
	ocl->oc_charged = (oflags >> 26) & 1;
	ocl->oc_unique = (oflags >> 25) & 1;
	ocl->oc_nowish = (oflags >> 24) & 1;
	ocl->oc_big = (oflags >> 23) & 1;
	ocl->oc_tough = (oflags >> 22) & 1;
	ocl->oc_dir = (oflags >> 20) & 3;
	ocl->oc_material = (oflags >> 15) & 31;
	
	ocl->oc_name_idx = mread16(mf);
	ocl->oc_descr_idx = mread16(mf);
	ocl->oc_weight = mread16(mf);
	ocl->oc_prob = mread16(mf);
	ocl->oc_cost = mread16(mf);
	ocl->oc_nutrition = mread16(mf);
	
	ocl->oc_subtyp = mread8(mf);
	ocl->oc_oprop = mread8(mf);
	ocl->oc_class = mread8(mf);
	ocl->oc_delay = mread8(mf);
	ocl->oc_color = mread8(mf);
	ocl->oc_wsdam = mread8(mf);
	ocl->oc_wldam = mread8(mf);
	ocl->oc_oc1 = mread8(mf);
	ocl->oc_oc2 = mread8(mf);
	
	ocl->oc_uname = NULL;
	namelen = mread32(mf);
	if (namelen) {
	    ocl->oc_uname = malloc(namelen);
	    mread(mf, ocl->oc_uname, namelen);
	}
	    
}


void restnames(struct memfile *mf)
{
	int i;
	
	mfmagic_check(mf, OCLASSES_MAGIC);

	for (i = 0; i < MAXOCLASSES; i++)
	    bases[i] = mread32(mf);
	
	for (i = 0; i < NUM_OBJECTS; i++)
	    disco[i] = mread32(mf);
	
	for (i = 0; i < NUM_OBJECTS; i++)
	    restobjclass(mf, &objects[i]);
}


void discover_object(int oindx, boolean mark_as_known, boolean credit_hero)
{
    if (!objects[oindx].oc_name_known) {
	int dindx, acls = objects[oindx].oc_class;

	/* Loop thru disco[] 'til we find the target (which may have been
	   uname'd) or the next open slot; one or the other will be found
	   before we reach the next class...
	 */
	for (dindx = bases[acls]; disco[dindx] != 0; dindx++)
	    if (disco[dindx] == oindx) break;
	disco[dindx] = oindx;

	if (mark_as_known) {
	    objects[oindx].oc_name_known = 1;
	    if (credit_hero) exercise(A_WIS, TRUE);

	    if (Is_dragon_scales(oindx))
		discover_object(Dragon_scales_to_mail(oindx), mark_as_known, FALSE);
	    else if (Is_dragon_mail(oindx))
		discover_object(Dragon_mail_to_scales(oindx), mark_as_known, FALSE);
	}
	if (moves > 1L) update_inventory();
    }
}

/* if a class name has been cleared, we may need to purge it from disco[] */
void undiscover_object(int oindx)
{
    if (!objects[oindx].oc_name_known) {
	int dindx, acls = objects[oindx].oc_class;
	boolean found = FALSE;

	/* find the object; shift those behind it forward one slot */
	for (dindx = bases[acls];
	      dindx < NUM_OBJECTS && disco[dindx] != 0
		&& objects[dindx].oc_class == acls; dindx++)
	    if (found)
		disco[dindx-1] = disco[dindx];
	    else if (disco[dindx] == oindx)
		found = TRUE;

	/* clear last slot */
	if (found) disco[dindx-1] = 0;

	update_inventory();
    }
}

void makeknown_msg(int otyp)
{
    boolean was_known, now_known;
    char oclass = objects[otyp].oc_class;
    schar osubtyp = objects[otyp].oc_subtyp;

    was_known = objects[otyp].oc_name_known;
    makeknown(otyp);
    now_known = objects[otyp].oc_name_known;

    if (flags.verbose && !was_known && now_known) {
	if (otyp == LENSES ||
	    (oclass == ARMOR_CLASS &&
	     (osubtyp == ARM_BOOTS || osubtyp == ARM_GLOVES))) {
	    pline("They must be %s!", simple_typename(otyp));
	} else {
	    pline("It must be %s!", an(simple_typename(otyp)));
	}
    }
}

static boolean interesting_to_discover(int i)
{
	/* Pre-discovered objects are now printed with a '*' */
    return((boolean)(objects[i].oc_uname != NULL ||
	    (objects[i].oc_name_known && OBJ_DESCR(objects[i]) != NULL)));
}

/* items that should stand out once they're known */
static const short uniq_objs[] = {
	AMULET_OF_YENDOR,
	SPE_BOOK_OF_THE_DEAD,
	CANDELABRUM_OF_INVOCATION,
	BELL_OF_OPENING,
};

int dodiscovered(void)
{
    int i, dis;
    int	ct = 0;
    char *s, oclass, prev_class, classes[MAXOCLASSES];
    struct menulist menu;
    char buf[BUFSZ];

    init_menulist(&menu);
    add_menutext(&menu, "Discoveries");
    add_menutext(&menu, "");

    /* gather "unique objects" into a pseudo-class; note that they'll
       also be displayed individually within their regular class */
    for (i = dis = 0; i < SIZE(uniq_objs); i++)
	if (objects[uniq_objs[i]].oc_name_known) {
	    if (!dis++)
		add_menuheading(&menu, "Unique Items");
	    sprintf(buf, "  %s", OBJ_NAME(objects[uniq_objs[i]]));
	    add_menutext(&menu, buf);
	    ++ct;
	}
    /* display any known artifacts as another pseudo-class */
    ct += disp_artifact_discoveries(&menu);

    /* several classes are omitted from packorder; one is of interest here */
    strcpy(classes, flags.inv_order);
    if (!strchr(classes, VENOM_CLASS)) {
	s = eos(classes);
	*s++ = VENOM_CLASS;
	*s = '\0';
    }

    for (s = classes; *s; s++) {
	oclass = *s;
	prev_class = oclass + 1;	/* forced different from oclass */
	for (i = bases[(int)oclass];
	     i < NUM_OBJECTS && objects[i].oc_class == oclass; i++) {
	    if ((dis = disco[i]) && interesting_to_discover(dis)) {
		ct++;
		if (oclass != prev_class) {
		    add_menuheading(&menu, let_to_name(oclass, FALSE));
		    prev_class = oclass;
		}
		sprintf(buf, "%s %s",(objects[dis].oc_pre_discovered ? "*" : " "),
				obj_typename(dis));
		add_menutext(&menu, buf);
	    }
	}
    }
    if (ct == 0) {
	pline("You haven't discovered anything yet...");
    } else
	display_menu(menu.items, menu.icount, NULL, PICK_NONE, NULL);
    free(menu.items);

    return 0;
}

/*o_init.c*/
