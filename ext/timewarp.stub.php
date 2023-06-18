<?php

/** @generate-class-entries */

namespace TimeWarp;

interface QueryReplacerInterface
{
    public function transform(string $query, ?\DateTimeInterface $now = \null): ?string; 
}

interface ProviderInterface
{
    public function provide(string $datetime = 'now', ?\DateTimeZone $timezone = \null): \DateTimeInterface;
}

function timewarp_set(\TimeWarp\ProviderInterface $provider): void {}

function timewarp_now(): ?\DateTimeInterface {}

function timewarp_unset(): void {}

function pdo_register_query_replacer(string $pdoDriverName, \TimeWarp\QueryReplacerInterface $replacer): void {}

function pdo_unregister_query_replacer(string $pdoDriverName, \TimeWarp\QueryReplacerInterface $replacer): void {}
