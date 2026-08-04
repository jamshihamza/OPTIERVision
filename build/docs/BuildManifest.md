# OPTIER Vision Build Manifest

## Purpose

This document defines the build architecture of the OPTIER Vision solution.

The objective is to ensure every project shares the same compiler,
runtime, include paths and third-party dependencies.

---

## Build Folder

build/

    docs/
        BuildManifest.md
        BuildSystem.md

    props/
        Path.props
        Common.props

    templates/
        (future)

---

## Rules

1. No project shall contain duplicated compiler settings.

2. Common configuration belongs in .props files.

3. Every new project must build without manual configuration.

4. Project-specific settings remain inside the .vcxproj.

5. Third-party libraries shall be configured only once.

---

## Current Status

Milestone BS-2

Build infrastructure freeze in progress.