-module(mmath_bin).

-include("mmath.hrl").

-export([convert/1, from_list/1, to_list/1, empty/1, length/1]).

from_list([]) ->
    <<>>;

from_list([_V0 | _] = L) when is_integer(_V0) ->
    << <<?INT:?TYPE_SIZE, V:?BITS/?INT_TYPE>> || V <- L >>.

to_list(Bin) ->
    to_list_int(Bin, 0, []).

to_list_int(<<?INT:?TYPE_SIZE, I:?BITS/?INT_TYPE, R/binary>>, _, Acc) ->
    to_list_int(R, I, [I | Acc]);
to_list_int(<<?NONE:?TYPE_SIZE, _:?BITS/?INT_TYPE, R/binary>>, Last, Acc) ->
    to_list_int(R, Last, [Last | Acc]);
to_list_int(<<>>, _, Acc) ->
    lists:reverse(Acc).

length(B) ->
    trunc(byte_size(B)/?DATA_SIZE).

empty(Length) ->
    <<0:((?TYPE_SIZE + ?BITS)*Length)/?INT_TYPE>>.

convert(Data) ->
    convert(Data, <<>>).

convert(<<>>, Acc) ->
    Acc;
convert(<<0, _:64/?INT_TYPE, R/binary>>, Acc) ->
    convert(R, <<Acc/binary, ?NONE:?TYPE_SIZE, 0:?BITS/?INT_TYPE>>);
convert(<<1, I:64/?INT_TYPE, R/binary>>, Acc) ->
    convert(R, <<Acc/binary, ?INT:?TYPE_SIZE, I:?BITS/?INT_TYPE>>).
