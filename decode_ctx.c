#include "decode_ctx.h"
#include <postgres.h>
#include <port.h>

/* Shift `ProtobufDecodeCtx` to `bytes` bytes */
void protobuf_decode_ctx_shift(ProtobufDecodeCtx* ctx, uint64 bytes) {
	if(ctx->protobuf_size < bytes)
		ereport(ERROR,
			(
			 errcode(ERRCODE_INTERNAL_ERROR),
			 errmsg("Unexpected end of the protobuf data."),
			 errdetail("protobuf_decode_ctx_shift() - %lu bytes left while trying to skip next %lu bytes.",
				ctx->protobuf_size, bytes),
			 errhint("Protobuf data is corrupted or there is a bug in pg_protobuf.")
			));

	ctx->protobuf_data += bytes;
	ctx->protobuf_size -= bytes;
}
