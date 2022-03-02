# Generated by devtools/yamaker from nixpkgs 21.11.

LIBRARY(postgres)

OWNER(g:cpp-contrib)

VERSION(13.6)

ORIGINAL_SOURCE(mirror://postgresql/source/v13.6/postgresql-13.6.tar.bz2)

LICENSE(
    Apache-2.0 AND
    BSD-2-Clause-Views AND
    BSD-3-Clause AND
    BSL-1.0 AND
    Bison-exception-2.2 AND
    GPL-1.0-or-later AND
    GPL-3.0-or-later AND
    ISC AND
    LicenseRef-scancode-generic-exception AND
    LicenseRef-scancode-proprietary-license AND
    LicenseRef-scancode-warranty-disclaimer AND
    MIT AND
    Martin-Birgmeier AND
    PostgreSQL AND
    Public-Domain AND
    Spencer-99 AND
    TCL
)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/icu
    contrib/libs/libc_compat
    contrib/libs/libiconv
    contrib/libs/libxml
    contrib/libs/openssl
)

ADDINCL(
    contrib/libs/libiconv/include
    contrib/libs/postgresql/src/backend/bootstrap
    contrib/libs/postgresql/src/backend/parser
    contrib/libs/postgresql/src/backend/replication
    contrib/libs/postgresql/src/backend/replication/logical
    contrib/libs/postgresql/src/backend/utils/adt
    contrib/libs/postgresql/src/backend/utils/misc
    contrib/libs/postgresql/src/backend/utils/sort
    contrib/libs/postgresql/src/common
    contrib/libs/postgresql/src/include
    contrib/libs/postgresql/src/port
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

CFLAGS(
    -DDLSUFFIX=\".so\"
)

SRCS(
    src/backend/access/brin/brin.c
    src/backend/access/brin/brin_inclusion.c
    src/backend/access/brin/brin_minmax.c
    src/backend/access/brin/brin_pageops.c
    src/backend/access/brin/brin_revmap.c
    src/backend/access/brin/brin_tuple.c
    src/backend/access/brin/brin_validate.c
    src/backend/access/brin/brin_xlog.c
    src/backend/access/common/attmap.c
    src/backend/access/common/bufmask.c
    src/backend/access/common/detoast.c
    src/backend/access/common/heaptuple.c
    src/backend/access/common/indextuple.c
    src/backend/access/common/printsimple.c
    src/backend/access/common/printtup.c
    src/backend/access/common/relation.c
    src/backend/access/common/reloptions.c
    src/backend/access/common/scankey.c
    src/backend/access/common/session.c
    src/backend/access/common/toast_internals.c
    src/backend/access/common/tupconvert.c
    src/backend/access/common/tupdesc.c
    src/backend/access/gin/ginarrayproc.c
    src/backend/access/gin/ginbtree.c
    src/backend/access/gin/ginbulk.c
    src/backend/access/gin/gindatapage.c
    src/backend/access/gin/ginentrypage.c
    src/backend/access/gin/ginfast.c
    src/backend/access/gin/ginget.c
    src/backend/access/gin/gininsert.c
    src/backend/access/gin/ginlogic.c
    src/backend/access/gin/ginpostinglist.c
    src/backend/access/gin/ginscan.c
    src/backend/access/gin/ginutil.c
    src/backend/access/gin/ginvacuum.c
    src/backend/access/gin/ginvalidate.c
    src/backend/access/gin/ginxlog.c
    src/backend/access/gist/gist.c
    src/backend/access/gist/gistbuild.c
    src/backend/access/gist/gistbuildbuffers.c
    src/backend/access/gist/gistget.c
    src/backend/access/gist/gistproc.c
    src/backend/access/gist/gistscan.c
    src/backend/access/gist/gistsplit.c
    src/backend/access/gist/gistutil.c
    src/backend/access/gist/gistvacuum.c
    src/backend/access/gist/gistvalidate.c
    src/backend/access/gist/gistxlog.c
    src/backend/access/hash/hash.c
    src/backend/access/hash/hash_xlog.c
    src/backend/access/hash/hashfunc.c
    src/backend/access/hash/hashinsert.c
    src/backend/access/hash/hashovfl.c
    src/backend/access/hash/hashpage.c
    src/backend/access/hash/hashsearch.c
    src/backend/access/hash/hashsort.c
    src/backend/access/hash/hashutil.c
    src/backend/access/hash/hashvalidate.c
    src/backend/access/heap/heapam.c
    src/backend/access/heap/heapam_handler.c
    src/backend/access/heap/heapam_visibility.c
    src/backend/access/heap/heaptoast.c
    src/backend/access/heap/hio.c
    src/backend/access/heap/pruneheap.c
    src/backend/access/heap/rewriteheap.c
    src/backend/access/heap/syncscan.c
    src/backend/access/heap/vacuumlazy.c
    src/backend/access/heap/visibilitymap.c
    src/backend/access/index/amapi.c
    src/backend/access/index/amvalidate.c
    src/backend/access/index/genam.c
    src/backend/access/index/indexam.c
    src/backend/access/nbtree/nbtcompare.c
    src/backend/access/nbtree/nbtdedup.c
    src/backend/access/nbtree/nbtinsert.c
    src/backend/access/nbtree/nbtpage.c
    src/backend/access/nbtree/nbtree.c
    src/backend/access/nbtree/nbtsearch.c
    src/backend/access/nbtree/nbtsort.c
    src/backend/access/nbtree/nbtsplitloc.c
    src/backend/access/nbtree/nbtutils.c
    src/backend/access/nbtree/nbtvalidate.c
    src/backend/access/nbtree/nbtxlog.c
    src/backend/access/rmgrdesc/brindesc.c
    src/backend/access/rmgrdesc/clogdesc.c
    src/backend/access/rmgrdesc/committsdesc.c
    src/backend/access/rmgrdesc/dbasedesc.c
    src/backend/access/rmgrdesc/genericdesc.c
    src/backend/access/rmgrdesc/gindesc.c
    src/backend/access/rmgrdesc/gistdesc.c
    src/backend/access/rmgrdesc/hashdesc.c
    src/backend/access/rmgrdesc/heapdesc.c
    src/backend/access/rmgrdesc/logicalmsgdesc.c
    src/backend/access/rmgrdesc/mxactdesc.c
    src/backend/access/rmgrdesc/nbtdesc.c
    src/backend/access/rmgrdesc/relmapdesc.c
    src/backend/access/rmgrdesc/replorigindesc.c
    src/backend/access/rmgrdesc/seqdesc.c
    src/backend/access/rmgrdesc/smgrdesc.c
    src/backend/access/rmgrdesc/spgdesc.c
    src/backend/access/rmgrdesc/standbydesc.c
    src/backend/access/rmgrdesc/tblspcdesc.c
    src/backend/access/rmgrdesc/xactdesc.c
    src/backend/access/rmgrdesc/xlogdesc.c
    src/backend/access/spgist/spgdoinsert.c
    src/backend/access/spgist/spginsert.c
    src/backend/access/spgist/spgkdtreeproc.c
    src/backend/access/spgist/spgproc.c
    src/backend/access/spgist/spgquadtreeproc.c
    src/backend/access/spgist/spgscan.c
    src/backend/access/spgist/spgtextproc.c
    src/backend/access/spgist/spgutils.c
    src/backend/access/spgist/spgvacuum.c
    src/backend/access/spgist/spgvalidate.c
    src/backend/access/spgist/spgxlog.c
    src/backend/access/table/table.c
    src/backend/access/table/tableam.c
    src/backend/access/table/tableamapi.c
    src/backend/access/table/toast_helper.c
    src/backend/access/tablesample/bernoulli.c
    src/backend/access/tablesample/system.c
    src/backend/access/tablesample/tablesample.c
    src/backend/access/transam/clog.c
    src/backend/access/transam/commit_ts.c
    src/backend/access/transam/generic_xlog.c
    src/backend/access/transam/multixact.c
    src/backend/access/transam/parallel.c
    src/backend/access/transam/rmgr.c
    src/backend/access/transam/slru.c
    src/backend/access/transam/subtrans.c
    src/backend/access/transam/timeline.c
    src/backend/access/transam/transam.c
    src/backend/access/transam/twophase.c
    src/backend/access/transam/twophase_rmgr.c
    src/backend/access/transam/varsup.c
    src/backend/access/transam/xact.c
    src/backend/access/transam/xlog.c
    src/backend/access/transam/xlogarchive.c
    src/backend/access/transam/xlogfuncs.c
    src/backend/access/transam/xloginsert.c
    src/backend/access/transam/xlogreader.c
    src/backend/access/transam/xlogutils.c
    src/backend/bootstrap/bootparse.c
    src/backend/bootstrap/bootstrap.c
    src/backend/catalog/aclchk.c
    src/backend/catalog/catalog.c
    src/backend/catalog/dependency.c
    src/backend/catalog/heap.c
    src/backend/catalog/index.c
    src/backend/catalog/indexing.c
    src/backend/catalog/namespace.c
    src/backend/catalog/objectaccess.c
    src/backend/catalog/objectaddress.c
    src/backend/catalog/partition.c
    src/backend/catalog/pg_aggregate.c
    src/backend/catalog/pg_cast.c
    src/backend/catalog/pg_collation.c
    src/backend/catalog/pg_constraint.c
    src/backend/catalog/pg_conversion.c
    src/backend/catalog/pg_db_role_setting.c
    src/backend/catalog/pg_depend.c
    src/backend/catalog/pg_enum.c
    src/backend/catalog/pg_inherits.c
    src/backend/catalog/pg_largeobject.c
    src/backend/catalog/pg_namespace.c
    src/backend/catalog/pg_operator.c
    src/backend/catalog/pg_proc.c
    src/backend/catalog/pg_publication.c
    src/backend/catalog/pg_range.c
    src/backend/catalog/pg_shdepend.c
    src/backend/catalog/pg_subscription.c
    src/backend/catalog/pg_type.c
    src/backend/catalog/storage.c
    src/backend/catalog/toasting.c
    src/backend/commands/aggregatecmds.c
    src/backend/commands/alter.c
    src/backend/commands/amcmds.c
    src/backend/commands/analyze.c
    src/backend/commands/async.c
    src/backend/commands/cluster.c
    src/backend/commands/collationcmds.c
    src/backend/commands/comment.c
    src/backend/commands/constraint.c
    src/backend/commands/conversioncmds.c
    src/backend/commands/copy.c
    src/backend/commands/createas.c
    src/backend/commands/dbcommands.c
    src/backend/commands/define.c
    src/backend/commands/discard.c
    src/backend/commands/dropcmds.c
    src/backend/commands/event_trigger.c
    src/backend/commands/explain.c
    src/backend/commands/extension.c
    src/backend/commands/foreigncmds.c
    src/backend/commands/functioncmds.c
    src/backend/commands/indexcmds.c
    src/backend/commands/lockcmds.c
    src/backend/commands/matview.c
    src/backend/commands/opclasscmds.c
    src/backend/commands/operatorcmds.c
    src/backend/commands/policy.c
    src/backend/commands/portalcmds.c
    src/backend/commands/prepare.c
    src/backend/commands/proclang.c
    src/backend/commands/publicationcmds.c
    src/backend/commands/schemacmds.c
    src/backend/commands/seclabel.c
    src/backend/commands/sequence.c
    src/backend/commands/statscmds.c
    src/backend/commands/subscriptioncmds.c
    src/backend/commands/tablecmds.c
    src/backend/commands/tablespace.c
    src/backend/commands/trigger.c
    src/backend/commands/tsearchcmds.c
    src/backend/commands/typecmds.c
    src/backend/commands/user.c
    src/backend/commands/vacuum.c
    src/backend/commands/variable.c
    src/backend/commands/view.c
    src/backend/executor/execAmi.c
    src/backend/executor/execCurrent.c
    src/backend/executor/execExpr.c
    src/backend/executor/execExprInterp.c
    src/backend/executor/execGrouping.c
    src/backend/executor/execIndexing.c
    src/backend/executor/execJunk.c
    src/backend/executor/execMain.c
    src/backend/executor/execParallel.c
    src/backend/executor/execPartition.c
    src/backend/executor/execProcnode.c
    src/backend/executor/execReplication.c
    src/backend/executor/execSRF.c
    src/backend/executor/execScan.c
    src/backend/executor/execTuples.c
    src/backend/executor/execUtils.c
    src/backend/executor/functions.c
    src/backend/executor/instrument.c
    src/backend/executor/nodeAgg.c
    src/backend/executor/nodeAppend.c
    src/backend/executor/nodeBitmapAnd.c
    src/backend/executor/nodeBitmapHeapscan.c
    src/backend/executor/nodeBitmapIndexscan.c
    src/backend/executor/nodeBitmapOr.c
    src/backend/executor/nodeCtescan.c
    src/backend/executor/nodeCustom.c
    src/backend/executor/nodeForeignscan.c
    src/backend/executor/nodeFunctionscan.c
    src/backend/executor/nodeGather.c
    src/backend/executor/nodeGatherMerge.c
    src/backend/executor/nodeGroup.c
    src/backend/executor/nodeHash.c
    src/backend/executor/nodeHashjoin.c
    src/backend/executor/nodeIncrementalSort.c
    src/backend/executor/nodeIndexonlyscan.c
    src/backend/executor/nodeIndexscan.c
    src/backend/executor/nodeLimit.c
    src/backend/executor/nodeLockRows.c
    src/backend/executor/nodeMaterial.c
    src/backend/executor/nodeMergeAppend.c
    src/backend/executor/nodeMergejoin.c
    src/backend/executor/nodeModifyTable.c
    src/backend/executor/nodeNamedtuplestorescan.c
    src/backend/executor/nodeNestloop.c
    src/backend/executor/nodeProjectSet.c
    src/backend/executor/nodeRecursiveunion.c
    src/backend/executor/nodeResult.c
    src/backend/executor/nodeSamplescan.c
    src/backend/executor/nodeSeqscan.c
    src/backend/executor/nodeSetOp.c
    src/backend/executor/nodeSort.c
    src/backend/executor/nodeSubplan.c
    src/backend/executor/nodeSubqueryscan.c
    src/backend/executor/nodeTableFuncscan.c
    src/backend/executor/nodeTidscan.c
    src/backend/executor/nodeUnique.c
    src/backend/executor/nodeValuesscan.c
    src/backend/executor/nodeWindowAgg.c
    src/backend/executor/nodeWorktablescan.c
    src/backend/executor/spi.c
    src/backend/executor/tqueue.c
    src/backend/executor/tstoreReceiver.c
    src/backend/foreign/foreign.c
    src/backend/jit/jit.c
    src/backend/lib/binaryheap.c
    src/backend/lib/bipartite_match.c
    src/backend/lib/bloomfilter.c
    src/backend/lib/dshash.c
    src/backend/lib/hyperloglog.c
    src/backend/lib/ilist.c
    src/backend/lib/integerset.c
    src/backend/lib/knapsack.c
    src/backend/lib/pairingheap.c
    src/backend/lib/rbtree.c
    src/backend/libpq/auth-scram.c
    src/backend/libpq/auth.c
    src/backend/libpq/be-fsstubs.c
    src/backend/libpq/be-secure-common.c
    src/backend/libpq/be-secure-openssl.c
    src/backend/libpq/be-secure.c
    src/backend/libpq/crypt.c
    src/backend/libpq/hba.c
    src/backend/libpq/ifaddr.c
    src/backend/libpq/pqcomm.c
    src/backend/libpq/pqformat.c
    src/backend/libpq/pqmq.c
    src/backend/libpq/pqsignal.c
    src/backend/nodes/bitmapset.c
    src/backend/nodes/copyfuncs.c
    src/backend/nodes/equalfuncs.c
    src/backend/nodes/extensible.c
    src/backend/nodes/list.c
    src/backend/nodes/makefuncs.c
    src/backend/nodes/nodeFuncs.c
    src/backend/nodes/nodes.c
    src/backend/nodes/outfuncs.c
    src/backend/nodes/params.c
    src/backend/nodes/print.c
    src/backend/nodes/read.c
    src/backend/nodes/readfuncs.c
    src/backend/nodes/tidbitmap.c
    src/backend/nodes/value.c
    src/backend/optimizer/geqo/geqo_copy.c
    src/backend/optimizer/geqo/geqo_cx.c
    src/backend/optimizer/geqo/geqo_erx.c
    src/backend/optimizer/geqo/geqo_eval.c
    src/backend/optimizer/geqo/geqo_main.c
    src/backend/optimizer/geqo/geqo_misc.c
    src/backend/optimizer/geqo/geqo_mutation.c
    src/backend/optimizer/geqo/geqo_ox1.c
    src/backend/optimizer/geqo/geqo_ox2.c
    src/backend/optimizer/geqo/geqo_pmx.c
    src/backend/optimizer/geqo/geqo_pool.c
    src/backend/optimizer/geqo/geqo_px.c
    src/backend/optimizer/geqo/geqo_random.c
    src/backend/optimizer/geqo/geqo_recombination.c
    src/backend/optimizer/geqo/geqo_selection.c
    src/backend/optimizer/path/allpaths.c
    src/backend/optimizer/path/clausesel.c
    src/backend/optimizer/path/costsize.c
    src/backend/optimizer/path/equivclass.c
    src/backend/optimizer/path/indxpath.c
    src/backend/optimizer/path/joinpath.c
    src/backend/optimizer/path/joinrels.c
    src/backend/optimizer/path/pathkeys.c
    src/backend/optimizer/path/tidpath.c
    src/backend/optimizer/plan/analyzejoins.c
    src/backend/optimizer/plan/createplan.c
    src/backend/optimizer/plan/initsplan.c
    src/backend/optimizer/plan/planagg.c
    src/backend/optimizer/plan/planmain.c
    src/backend/optimizer/plan/planner.c
    src/backend/optimizer/plan/setrefs.c
    src/backend/optimizer/plan/subselect.c
    src/backend/optimizer/prep/prepjointree.c
    src/backend/optimizer/prep/prepqual.c
    src/backend/optimizer/prep/preptlist.c
    src/backend/optimizer/prep/prepunion.c
    src/backend/optimizer/util/appendinfo.c
    src/backend/optimizer/util/clauses.c
    src/backend/optimizer/util/inherit.c
    src/backend/optimizer/util/joininfo.c
    src/backend/optimizer/util/orclauses.c
    src/backend/optimizer/util/paramassign.c
    src/backend/optimizer/util/pathnode.c
    src/backend/optimizer/util/placeholder.c
    src/backend/optimizer/util/plancat.c
    src/backend/optimizer/util/predtest.c
    src/backend/optimizer/util/relnode.c
    src/backend/optimizer/util/restrictinfo.c
    src/backend/optimizer/util/tlist.c
    src/backend/optimizer/util/var.c
    src/backend/parser/analyze.c
    src/backend/parser/gram.c
    src/backend/parser/parse_agg.c
    src/backend/parser/parse_clause.c
    src/backend/parser/parse_coerce.c
    src/backend/parser/parse_collate.c
    src/backend/parser/parse_cte.c
    src/backend/parser/parse_enr.c
    src/backend/parser/parse_expr.c
    src/backend/parser/parse_func.c
    src/backend/parser/parse_node.c
    src/backend/parser/parse_oper.c
    src/backend/parser/parse_param.c
    src/backend/parser/parse_relation.c
    src/backend/parser/parse_target.c
    src/backend/parser/parse_type.c
    src/backend/parser/parse_utilcmd.c
    src/backend/parser/parser.c
    src/backend/parser/scan.c
    src/backend/parser/scansup.c
    src/backend/partitioning/partbounds.c
    src/backend/partitioning/partdesc.c
    src/backend/partitioning/partprune.c
    src/backend/port/atomics.c
    src/backend/postmaster/autovacuum.c
    src/backend/postmaster/bgworker.c
    src/backend/postmaster/bgwriter.c
    src/backend/postmaster/checkpointer.c
    src/backend/postmaster/fork_process.c
    src/backend/postmaster/interrupt.c
    src/backend/postmaster/pgarch.c
    src/backend/postmaster/pgstat.c
    src/backend/postmaster/postmaster.c
    src/backend/postmaster/startup.c
    src/backend/postmaster/syslogger.c
    src/backend/postmaster/walwriter.c
    src/backend/regex/regcomp.c
    src/backend/regex/regerror.c
    src/backend/regex/regexec.c
    src/backend/regex/regexport.c
    src/backend/regex/regfree.c
    src/backend/regex/regprefix.c
    src/backend/replication/backup_manifest.c
    src/backend/replication/basebackup.c
    src/backend/replication/logical/decode.c
    src/backend/replication/logical/launcher.c
    src/backend/replication/logical/logical.c
    src/backend/replication/logical/logicalfuncs.c
    src/backend/replication/logical/message.c
    src/backend/replication/logical/origin.c
    src/backend/replication/logical/proto.c
    src/backend/replication/logical/relation.c
    src/backend/replication/logical/reorderbuffer.c
    src/backend/replication/logical/snapbuild.c
    src/backend/replication/logical/tablesync.c
    src/backend/replication/logical/worker.c
    src/backend/replication/repl_gram.c
    src/backend/replication/slot.c
    src/backend/replication/slotfuncs.c
    src/backend/replication/syncrep.c
    src/backend/replication/syncrep_gram.c
    src/backend/replication/walreceiver.c
    src/backend/replication/walreceiverfuncs.c
    src/backend/replication/walsender.c
    src/backend/rewrite/rewriteDefine.c
    src/backend/rewrite/rewriteHandler.c
    src/backend/rewrite/rewriteManip.c
    src/backend/rewrite/rewriteRemove.c
    src/backend/rewrite/rewriteSupport.c
    src/backend/rewrite/rowsecurity.c
    src/backend/statistics/dependencies.c
    src/backend/statistics/extended_stats.c
    src/backend/statistics/mcv.c
    src/backend/statistics/mvdistinct.c
    src/backend/storage/buffer/buf_init.c
    src/backend/storage/buffer/buf_table.c
    src/backend/storage/buffer/bufmgr.c
    src/backend/storage/buffer/freelist.c
    src/backend/storage/buffer/localbuf.c
    src/backend/storage/file/buffile.c
    src/backend/storage/file/copydir.c
    src/backend/storage/file/fd.c
    src/backend/storage/file/reinit.c
    src/backend/storage/file/sharedfileset.c
    src/backend/storage/freespace/freespace.c
    src/backend/storage/freespace/fsmpage.c
    src/backend/storage/freespace/indexfsm.c
    src/backend/storage/ipc/barrier.c
    src/backend/storage/ipc/dsm.c
    src/backend/storage/ipc/dsm_impl.c
    src/backend/storage/ipc/ipc.c
    src/backend/storage/ipc/ipci.c
    src/backend/storage/ipc/latch.c
    src/backend/storage/ipc/pmsignal.c
    src/backend/storage/ipc/procarray.c
    src/backend/storage/ipc/procsignal.c
    src/backend/storage/ipc/shm_mq.c
    src/backend/storage/ipc/shm_toc.c
    src/backend/storage/ipc/shmem.c
    src/backend/storage/ipc/shmqueue.c
    src/backend/storage/ipc/signalfuncs.c
    src/backend/storage/ipc/sinval.c
    src/backend/storage/ipc/sinvaladt.c
    src/backend/storage/ipc/standby.c
    src/backend/storage/large_object/inv_api.c
    src/backend/storage/lmgr/condition_variable.c
    src/backend/storage/lmgr/deadlock.c
    src/backend/storage/lmgr/lmgr.c
    src/backend/storage/lmgr/lock.c
    src/backend/storage/lmgr/lwlock.c
    src/backend/storage/lmgr/lwlocknames.c
    src/backend/storage/lmgr/predicate.c
    src/backend/storage/lmgr/proc.c
    src/backend/storage/lmgr/s_lock.c
    src/backend/storage/lmgr/spin.c
    src/backend/storage/page/bufpage.c
    src/backend/storage/page/checksum.c
    src/backend/storage/page/itemptr.c
    src/backend/storage/smgr/md.c
    src/backend/storage/smgr/smgr.c
    src/backend/storage/sync/sync.c
    src/backend/tcop/cmdtag.c
    src/backend/tcop/dest.c
    src/backend/tcop/fastpath.c
    src/backend/tcop/postgres.c
    src/backend/tcop/pquery.c
    src/backend/tcop/utility.c
    src/backend/tsearch/dict.c
    src/backend/tsearch/dict_ispell.c
    src/backend/tsearch/dict_simple.c
    src/backend/tsearch/dict_synonym.c
    src/backend/tsearch/dict_thesaurus.c
    src/backend/tsearch/regis.c
    src/backend/tsearch/spell.c
    src/backend/tsearch/to_tsany.c
    src/backend/tsearch/ts_locale.c
    src/backend/tsearch/ts_parse.c
    src/backend/tsearch/ts_selfuncs.c
    src/backend/tsearch/ts_typanalyze.c
    src/backend/tsearch/ts_utils.c
    src/backend/tsearch/wparser.c
    src/backend/tsearch/wparser_def.c
    src/backend/utils/adt/acl.c
    src/backend/utils/adt/amutils.c
    src/backend/utils/adt/array_expanded.c
    src/backend/utils/adt/array_selfuncs.c
    src/backend/utils/adt/array_typanalyze.c
    src/backend/utils/adt/array_userfuncs.c
    src/backend/utils/adt/arrayfuncs.c
    src/backend/utils/adt/arrayutils.c
    src/backend/utils/adt/ascii.c
    src/backend/utils/adt/bool.c
    src/backend/utils/adt/cash.c
    src/backend/utils/adt/char.c
    src/backend/utils/adt/cryptohashes.c
    src/backend/utils/adt/date.c
    src/backend/utils/adt/datetime.c
    src/backend/utils/adt/datum.c
    src/backend/utils/adt/dbsize.c
    src/backend/utils/adt/domains.c
    src/backend/utils/adt/encode.c
    src/backend/utils/adt/enum.c
    src/backend/utils/adt/expandeddatum.c
    src/backend/utils/adt/expandedrecord.c
    src/backend/utils/adt/float.c
    src/backend/utils/adt/format_type.c
    src/backend/utils/adt/formatting.c
    src/backend/utils/adt/genfile.c
    src/backend/utils/adt/geo_ops.c
    src/backend/utils/adt/geo_selfuncs.c
    src/backend/utils/adt/geo_spgist.c
    src/backend/utils/adt/inet_cidr_ntop.c
    src/backend/utils/adt/inet_net_pton.c
    src/backend/utils/adt/int.c
    src/backend/utils/adt/int8.c
    src/backend/utils/adt/json.c
    src/backend/utils/adt/jsonb.c
    src/backend/utils/adt/jsonb_gin.c
    src/backend/utils/adt/jsonb_op.c
    src/backend/utils/adt/jsonb_util.c
    src/backend/utils/adt/jsonfuncs.c
    src/backend/utils/adt/jsonpath.c
    src/backend/utils/adt/jsonpath_exec.c
    src/backend/utils/adt/jsonpath_gram.c
    src/backend/utils/adt/like.c
    src/backend/utils/adt/like_support.c
    src/backend/utils/adt/lockfuncs.c
    src/backend/utils/adt/mac.c
    src/backend/utils/adt/mac8.c
    src/backend/utils/adt/misc.c
    src/backend/utils/adt/name.c
    src/backend/utils/adt/network.c
    src/backend/utils/adt/network_gist.c
    src/backend/utils/adt/network_selfuncs.c
    src/backend/utils/adt/network_spgist.c
    src/backend/utils/adt/numeric.c
    src/backend/utils/adt/numutils.c
    src/backend/utils/adt/oid.c
    src/backend/utils/adt/oracle_compat.c
    src/backend/utils/adt/orderedsetaggs.c
    src/backend/utils/adt/partitionfuncs.c
    src/backend/utils/adt/pg_locale.c
    src/backend/utils/adt/pg_lsn.c
    src/backend/utils/adt/pg_upgrade_support.c
    src/backend/utils/adt/pgstatfuncs.c
    src/backend/utils/adt/pseudotypes.c
    src/backend/utils/adt/quote.c
    src/backend/utils/adt/rangetypes.c
    src/backend/utils/adt/rangetypes_gist.c
    src/backend/utils/adt/rangetypes_selfuncs.c
    src/backend/utils/adt/rangetypes_spgist.c
    src/backend/utils/adt/rangetypes_typanalyze.c
    src/backend/utils/adt/regexp.c
    src/backend/utils/adt/regproc.c
    src/backend/utils/adt/ri_triggers.c
    src/backend/utils/adt/rowtypes.c
    src/backend/utils/adt/ruleutils.c
    src/backend/utils/adt/selfuncs.c
    src/backend/utils/adt/tid.c
    src/backend/utils/adt/timestamp.c
    src/backend/utils/adt/trigfuncs.c
    src/backend/utils/adt/tsginidx.c
    src/backend/utils/adt/tsgistidx.c
    src/backend/utils/adt/tsquery.c
    src/backend/utils/adt/tsquery_cleanup.c
    src/backend/utils/adt/tsquery_gist.c
    src/backend/utils/adt/tsquery_op.c
    src/backend/utils/adt/tsquery_rewrite.c
    src/backend/utils/adt/tsquery_util.c
    src/backend/utils/adt/tsrank.c
    src/backend/utils/adt/tsvector.c
    src/backend/utils/adt/tsvector_op.c
    src/backend/utils/adt/tsvector_parser.c
    src/backend/utils/adt/uuid.c
    src/backend/utils/adt/varbit.c
    src/backend/utils/adt/varchar.c
    src/backend/utils/adt/varlena.c
    src/backend/utils/adt/version.c
    src/backend/utils/adt/windowfuncs.c
    src/backend/utils/adt/xid.c
    src/backend/utils/adt/xid8funcs.c
    src/backend/utils/adt/xml.c
    src/backend/utils/cache/attoptcache.c
    src/backend/utils/cache/catcache.c
    src/backend/utils/cache/evtcache.c
    src/backend/utils/cache/inval.c
    src/backend/utils/cache/lsyscache.c
    src/backend/utils/cache/partcache.c
    src/backend/utils/cache/plancache.c
    src/backend/utils/cache/relcache.c
    src/backend/utils/cache/relfilenodemap.c
    src/backend/utils/cache/relmapper.c
    src/backend/utils/cache/spccache.c
    src/backend/utils/cache/syscache.c
    src/backend/utils/cache/ts_cache.c
    src/backend/utils/cache/typcache.c
    src/backend/utils/error/assert.c
    src/backend/utils/error/elog.c
    src/backend/utils/fmgr/dfmgr.c
    src/backend/utils/fmgr/fmgr.c
    src/backend/utils/fmgr/funcapi.c
    src/backend/utils/fmgrtab.c
    src/backend/utils/hash/dynahash.c
    src/backend/utils/hash/pg_crc.c
    src/backend/utils/init/globals.c
    src/backend/utils/init/miscinit.c
    src/backend/utils/init/postinit.c
    src/backend/utils/mb/conv.c
    src/backend/utils/mb/mbutils.c
    src/backend/utils/mb/stringinfo_mb.c
    src/backend/utils/mb/wstrcmp.c
    src/backend/utils/mb/wstrncmp.c
    src/backend/utils/misc/guc.c
    src/backend/utils/misc/help_config.c
    src/backend/utils/misc/pg_config.c
    src/backend/utils/misc/pg_controldata.c
    src/backend/utils/misc/pg_rusage.c
    src/backend/utils/misc/ps_status.c
    src/backend/utils/misc/queryenvironment.c
    src/backend/utils/misc/rls.c
    src/backend/utils/misc/sampling.c
    src/backend/utils/misc/superuser.c
    src/backend/utils/misc/timeout.c
    src/backend/utils/misc/tzparser.c
    src/backend/utils/mmgr/aset.c
    src/backend/utils/mmgr/dsa.c
    src/backend/utils/mmgr/freepage.c
    src/backend/utils/mmgr/generation.c
    src/backend/utils/mmgr/mcxt.c
    src/backend/utils/mmgr/memdebug.c
    src/backend/utils/mmgr/portalmem.c
    src/backend/utils/mmgr/slab.c
    src/backend/utils/resowner/resowner.c
    src/backend/utils/sort/logtape.c
    src/backend/utils/sort/sharedtuplestore.c
    src/backend/utils/sort/sortsupport.c
    src/backend/utils/sort/tuplesort.c
    src/backend/utils/sort/tuplestore.c
    src/backend/utils/time/combocid.c
    src/backend/utils/time/snapmgr.c
    src/common/archive.c
    src/common/base64.c
    src/common/checksum_helper.c
    src/common/config_info.c
    src/common/controldata_utils.c
    src/common/d2s.c
    src/common/encnames.c
    src/common/exec.c
    src/common/f2s.c
    src/common/file_perm.c
    src/common/hashfn.c
    src/common/ip.c
    src/common/jsonapi.c
    src/common/keywords.c
    src/common/kwlookup.c
    src/common/link-canary.c
    src/common/md5.c
    src/common/pg_lzcompress.c
    src/common/pgfnames.c
    src/common/protocol_openssl.c
    src/common/psprintf.c
    src/common/relpath.c
    src/common/rmtree.c
    src/common/saslprep.c
    src/common/scram-common.c
    src/common/sha2_openssl.c
    src/common/string.c
    src/common/stringinfo.c
    src/common/unicode_norm.c
    src/common/username.c
    src/common/wait_error.c
    src/common/wchar.c
    src/port/chklocale.c
    src/port/erand48.c
    src/port/fls.c
    src/port/getpeereid.c
    src/port/inet_net_ntop.c
    src/port/noblock.c
    src/port/path.c
    src/port/pg_bitutils.c
    src/port/pg_crc32c_sb8.c
    src/port/pg_crc32c_sse42.c
    src/port/pg_crc32c_sse42_choose.c
    src/port/pg_strong_random.c
    src/port/pgcheckdir.c
    src/port/pgmkdirp.c
    src/port/pgsleep.c
    src/port/pgstrcasecmp.c
    src/port/pgstrsignal.c
    src/port/pqsignal.c
    src/port/qsort.c
    src/port/qsort_arg.c
    src/port/quotes.c
    src/port/snprintf.c
    src/port/sprompt.c
    src/port/strerror.c
    src/port/tar.c
    src/port/thread.c
    src/timezone/localtime.c
    src/timezone/pgtz.c
    src/timezone/strftime.c
)

IF (OS_LINUX OR OS_DARWIN)
    SRCS(
        src/backend/port/posix_sema.c
        src/backend/port/sysv_shmem.c
    )
ELSEIF (OS_WINDOWS)
    ADDINCL(
        contrib/libs/postgresql/src/include/port
        contrib/libs/postgresql/src/include/port/win32
        contrib/libs/postgresql/src/include/port/win32_msvc
    )
    SRCS(
        src/backend/port/win32/crashdump.c
        src/backend/port/win32/signal.c
        src/backend/port/win32/socket.c
        src/backend/port/win32/timer.c
        src/backend/port/win32_sema.c
        src/backend/port/win32_shmem.c
        src/port/dirmod.c
        src/port/dlopen.c
        src/port/getaddrinfo.c
        src/port/getopt.c
        src/port/getrusage.c
        src/port/gettimeofday.c
        src/port/inet_aton.c
        src/port/kill.c
        src/port/open.c
        src/port/pread.c
        src/port/pwrite.c
        src/port/system.c
        src/port/win32env.c
        src/port/win32error.c
        src/port/win32security.c
        src/port/win32setlocale.c
    )
ENDIF()

END()

RECURSE(
    bin/postgresql
)
