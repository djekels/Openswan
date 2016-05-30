#include "../lp13-parentI3/parentI3_head.c"

#define TESTNAME "rekeyikev2"
#define AFTER_CONN rekeyit

void rekeyit()
{
    struct state *st = NULL;
    struct pcr_kenonce *kn = &crypto_req->pcr_d.kn;

    fprintf(stderr, "now pretend that the keylife timer is up, and rekey the connection\n");

    timer_list();
    st = state_with_serialno(2);

    if(st) {
        DBG(DBG_LIFECYCLE
            , openswan_log("replacing stale %s SA"
                           , (IS_PHASE1(st->st_state)|| IS_PHASE15(st->st_state ))? "ISAKMP" : "IPsec"));
        ipsecdoi_replace(st, LEMPTY, LEMPTY, 1);
    } else {
        fprintf(stderr, "no state #2 found\n");
    }

    run_continuation(crypto_req);
}

#include "../lp13-parentI3/parentI3_main.c"

 /*
 * Local Variables:
 * c-style: pluto
 * c-basic-offset: 4
 * compile-command: "make check"
 * End:
 */
