

add_custom_target(check-all-libs
   DEPENDS check-cgen check-milk check-obcl
)

add_custom_target(check
   DEPENDS check-all-libs
)

