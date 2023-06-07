<?php

/** @generate-class-entries */

namespace TimeWarp;

interface QueryReplacerInterface
{
    public function transform(string $query, ?\DateTimeInterface $now = \null): string; 
}

function timewarp_set(\DateTimeInterface $now): void {}

function timewarp_unset(): void {}

function pdo_register_query_replacer(string $pdoDriverName, \TimeWarp\QueryReplacerInterface $replacer): void {}

function pdo_unregister_query_replacer(string $pdoDriverName, \TimeWarp\QueryReplacerInterface $replacer): void {}
