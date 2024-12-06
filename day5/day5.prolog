
%:- dynamic day5rule/2.
%loadRules:-
%    open('inputs/day5.prolog',read,Stream),
%    read_pairs(Stream),
%    close(Stream).
%
%read_pairs(Stream):-
%    \+ at_end_of_stream(Stream),
%    read(Stream, X),
%    assert(X),
%    read_pairs(Stream).

%day5update([97,61,53,29,13]).
%day5update([75,29,13]).
%day5update([75,97,47,61,53]).
%day5update([61,13,29]).
%day5update([97,13,75,29,47]).

%loadRules.

day5rule(47,53).
day5rule(97,13).
day5rule(97,61).
day5rule(97,47).
day5rule(75,29).
day5rule(61,13).
day5rule(75,53).
day5rule(29,13).
day5rule(97,29).
day5rule(53,29).
day5rule(61,53).
day5rule(97,53).
day5rule(61,29).
day5rule(47,13).
day5rule(75,47).
day5rule(97,75).
day5rule(47,61).
day5rule(75,61).
day5rule(47,29).
day5rule(75,13).
day5rule(53,13).

% Simple success cases:
% The page list is less than 2 pages
% The page list only contains one of the two rule pages
% Might be easier to assert for the one failure case:
% Fails when both pages in the rule are in

checkSingleRule(_,_,[]).
checkSingleRule(A,B,[B|Rest]):-
    \+ member(A,Rest).
checkSingleRule(A,B,[_|Rest]):-
    checkSingleRule(A,B,Rest).
    
%checkUpdate([], [75,47,61,53,29]).


